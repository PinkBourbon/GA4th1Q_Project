#include <stdio.h>

#include "RAGameEngine.h"
#include "RAGameObject.h"
#include <malloc.h>

#include "RARenderCore.h"
#include "RASingleList.h"
#include "RAInput.h"
#include "RATimer.h"
#include "RASound.h"
#include "RAType.h"

#define OBJECT_NUM (1000)

static RANode* _startGameObjects;
static RANode* _updateGameObjects;
static RANode* _noUpdateGameObjects;
static RANode* _disableGameObjects;

static RANode* _toEnableGameObjects;
static RANode* _toDisableGameObjects;

static GameObject* _gameObjects[OBJECT_NUM];

static HWND _hWnd;
static WCHAR _title[20];

bool _isEndGame = false;

static void input()
{
	KeyBoardInputHandler();
}

static RANode* GetListForState(eGameObjectState State)
{
	switch (State)
	{
		case GameObject_START:
		{
			return _startGameObjects;
		}
		break;

		case GameObject_UPDATE_TO_DISABLE:
			FALLTHROUGH;
		case GameObject_UPDATE:
		{
			return _updateGameObjects;
		}
		break;

		case GameObject_NOUPDATE:
		{
			return _noUpdateGameObjects;
		}
		break;

		case GameObject_DISABLE:
		{
			return _disableGameObjects;
		}
		break;

		default:
		{
			return NULL;
		}
		break;
	}
}

static void ChangeGameObjectState(GameObject* gameObject, eGameObjectState changeState)
{
	RANode* srcList = GetListForState(gameObject->state);
	RANode* dstList = GetListForState(changeState);

	MoveNode(srcList, gameObject, dstList);
	gameObject->state = changeState;
}

static void enableGameObject()
{
	RANode* currNode = _toEnableGameObjects->next;
	while (currNode != NULL)
	{
		RANode* nextNode = currNode->next;
		GameObject* currGameObject = currNode->data;

		ChangeGameObjectState(currGameObject, GameObject_START);
		if (currGameObject->animArray != NULL)
		{
			AddRenderTarget(currGameObject);
		}

		DeleteNode(_toEnableGameObjects, currGameObject);
		currNode = nextNode;
	}
}

static void disableGameObject()
{
	RANode* currNode = _toDisableGameObjects->next;
	while (currNode != NULL)
	{
		RANode* nextNode = currNode->next;
		GameObject* currGameObject = currNode->data;
		
		ChangeGameObjectState(currGameObject, GameObject_DISABLE);
		if (currGameObject->animArray != NULL)
		{
			DeleteRenderTarget(currGameObject);
		}

		DeleteNode(_toDisableGameObjects, currGameObject);
		currNode = nextNode;
	}
}

static void start()
{
	RANode* currNode = _startGameObjects->next;
	while (currNode != NULL)
	{
		GameObject* currGameObject = (GameObject*)(currNode->data);
		currNode = currNode->next;

		if (currGameObject->Start != NULL)
		{
			currGameObject->Start(currGameObject);
		}

		if (currGameObject->Update == NULL)
		{
			ChangeGameObjectState(currGameObject, GameObject_NOUPDATE);
		}
		else
		{
			ChangeGameObjectState(currGameObject, GameObject_UPDATE);
		}
	}
}

static void update(int64 deltaTime)
{
	RANode* currNode = _updateGameObjects->next;
	while (currNode != NULL)
	{
		GameObject* currGameObject = currNode->data;
		// ������Ʈ �濡 �ش� ������Ʈ�� disable�� ��쿡 �ش� ������Ʈ�� ����� �� �ֱ� ������
		// ���� ���� ��带 ����Ű�� �ϳ� �ѹ��� ���� ������Ʈ�� disable �� ��쿡�� ���� ������ �Ͼ��.
		currNode = currNode->next; 

		currGameObject->Update(currGameObject, deltaTime);
	}
	UpdateSound();
}

static void physics()
{

}

static void render(int64 deltaTime)
{
	//������ ���� ��.
	RenderToBackBuffer(deltaTime);
	DisplayBackBuffer();
}

void InitializeEngine(HWND hWnd, int32 screenWidth, int32 screenHeight)
{

	SetTimerFrequency();

	_startGameObjects = MakeNewList();
	_updateGameObjects = MakeNewList();
	_noUpdateGameObjects = MakeNewList();
	_disableGameObjects = MakeNewList();

	_toDisableGameObjects = MakeNewList();
	_toEnableGameObjects = MakeNewList();

	_hWnd = hWnd;

	// ��ǲ �ʱ�ȭ
	InitializeInput();

	// ������ ���� �ʱ�ȭ
	InitializeRenderCore(hWnd, screenWidth, screenHeight);

	// ���� ���� �ʱ�ȭ
	CreateSoundSystem();
}

void CloseEngine()
{
	CloseRenderCore();
}

void GameLoop()
{
	MSG msg;

	StartTimer();
	

	while (!_isEndGame)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)break;
			DispatchMessage(&msg);
		}
		else
		{
			int64 deltaTime = StopTimer();
			swprintf_s(_title, 20, TEXT("deltaTime : %lldms"), deltaTime);
			SetWindowTextW(_hWnd, _title); // ������ Ÿ��Ʋ�� deltaTime ǥ��
			StartTimer();
			enableGameObject();
			input();
			start();
			update(deltaTime);
			physics();
			render(deltaTime);
			disableGameObject();
		}
	}
}

GameObject* AllocGameObject()
{
	GameObject* gameObject = (GameObject*)malloc(sizeof(GameObject));

	if (gameObject == NULL)
	{
		return NULL;
	}

	memset(gameObject, 0, sizeof(gameObject));

	static gameObjectId = 0;

	gameObject->gameObjectID = gameObjectId;
	++gameObjectId;
	gameObject->state = GameObject_DISABLE;

	AddNode(_disableGameObjects, gameObject);

	return gameObject;
}

void FreeGameObject(GameObject* gameObject)
{
	RANode* list = GetListForState(gameObject->state);
	DeleteNode(list, gameObject);
	free(gameObject);
}

void EnableGameObject(GameObject* gameObject)
{
	AddNode(_toEnableGameObjects, gameObject);

	//ChangeGameObjectState(gameObject, GameObject_START);
	//if (gameObject->animArray != NULL)
	//{
	//	AddRenderTarget(gameObject);
	//}
}

void DisableGameObject(GameObject* gameObject)
{
	AddNode(_toDisableGameObjects, gameObject);

	//ChangeGameObjectState(gameObject, GameObject_DISABLE);
	//if (gameObject->animArray != NULL)
	//{
	//	DeleteRenderTarget(gameObject);
	//}
}

void ExitGame()
{
	_isEndGame = true;
}
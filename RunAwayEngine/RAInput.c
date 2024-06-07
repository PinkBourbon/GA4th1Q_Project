#include <Windows.h>
#include "RAInput.h"
#include "RAGameObject.h"
#include "RASingleList.h"
#include "RAType.h"
#include "RAMacro.h"


// gameobject가 NULL이면, 할당되지 않은 index라고 생각한다.
// array를 돌면서 할당된 녀석의 callback 만 호출해주면 된다.
// 할당이 되었다. = 키보드를 입력의 변화에 따른 callback함수 호출
//static keyCallback _keyCallbacks[100];
static RANode* _keyCallbackListHead;

static void CheckAndCallbackKey(int32 vkKey, bool* isDownKey)
{
	if (GetAsyncKeyState(vkKey) & 0x8001)
	{
		if (*isDownKey == false)
		{
			*isDownKey = true;
			RANode* currNode = _keyCallbackListHead->next;
			while (currNode != NULL)
			{
				KeyCallback* keyCallback = (KeyCallback*)(currNode->data);

				if (keyCallback->gameObject->state == GameObject_DISABLE)
				{
					currNode = currNode->next;
					continue;
				}

				keyCallback->_keyDownCallback(keyCallback->gameObject, vkKey);
				currNode = currNode->next;
			}
		}
	}
	else
	{
		if (*isDownKey == true)
		{
			*isDownKey = false;
			RANode* currNode = _keyCallbackListHead->next;
			while (currNode != NULL)
			{
				KeyCallback* keyCallback = (KeyCallback*)(currNode->data);

				if (keyCallback->gameObject->state == GameObject_DISABLE)
				{
					currNode = currNode->next;
					continue;
				}

				keyCallback->_keyUpCallback(keyCallback->gameObject, vkKey);
				currNode = currNode->next;
			}
		}
	}
}

void InitializeInput()
{
	_keyCallbackListHead = MakeNewList();
}

void KeyBoardInputHandler()
{
	// 8은 지금 내가(getasynckeystate를 호출한 시점)
	// 눌려져있는가
	// 1은 이 함수를 호출과 호출하는 사이, 그 시점에
	// 눌린적이 있는가?

	// 함수 호출이 기준인가? 호출사이의 간격인지는 확인해봐야함
		// left에 대한 이전 키 상태를 기억해야한다.
		// static 변수가 필요(바뀌면 안되니깐.)


	// assert 코드는 디버그에서만 작동한다.
	//Assert(_keyDownCallback, "함수포인터 세팅이 안됨.");
	//Assert(_keyUpCallback, "함수포인터 세팅이 안됨.");
	static bool isDownLeft = false;
	CheckAndCallbackKey(VK_LEFT, &isDownLeft);

	static bool isDownDown = false;
	CheckAndCallbackKey(VK_DOWN, &isDownDown);

	static bool isDownRight = false;
	CheckAndCallbackKey(VK_RIGHT, &isDownRight);

	static bool isDownUP = false;
	CheckAndCallbackKey(VK_UP, &isDownUP);

	static bool isDownA = false;
	CheckAndCallbackKey(0x41, &isDownA);

	static bool isDownS = false;
	CheckAndCallbackKey(0x53, &isDownS);

	static bool isDownF = false;
	CheckAndCallbackKey(0x46, &isDownF);

	static bool isDownSpace = false;
	CheckAndCallbackKey(VK_SPACE, &isDownSpace);

	static bool isDownEnter = false;
	CheckAndCallbackKey(VK_RETURN, &isDownEnter);

	static bool isDownESC = false;
	CheckAndCallbackKey(VK_ESCAPE, &isDownESC);
}

// keydowncallback이라는 함수포인터를 매개변수로 받는 함수 생성.
// 호출해주는게 아니라, 세팅해주는 녀석
// 대입 성공하면 true 실패하면 false
// keycallback를 세팅해주는 함수
// 비어있는걸 찾아서 세팅

void SetInputCallback(GameObject* obj, 
	void(*keyUpCallBack)(GameObject* this, int32 vkKey),
	void(*keyDownCallBack)(GameObject* this, int32 vkKey))
{
	KeyCallback* keyCallback = (KeyCallback*)malloc(sizeof(KeyCallback));
	if (keyCallback == NULL)
	{
		return;
	}

	keyCallback->gameObject = obj;
	keyCallback->_keyUpCallback = keyUpCallBack;
	keyCallback->_keyDownCallback = keyDownCallBack;

	AddNode(_keyCallbackListHead, keyCallback);
}
// 주의사항
// 현재 함수포인터를 1개만 등록할 수 있다.
// 게임 오브젝트별로 다른 함수들을 쓰려면 구조를 바꿔야한다.
// 이부분을 생각해봐라....(바꾸게 될것이다.)
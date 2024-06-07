#include "SceneCredit.h"
#include "RAGameEngine.h"
#include "RACamera.h"
#include "RAInput.h"

#include "SceneMgr.h"

#include "define.h"
#include "CreditWallPaper.h"

static bool _isNowEnable = false;

static RACamera* _camera;

static GameObject* _sceneCredit;

static GameObject* _creditWallPaper;

static void Start(GameObject* this)
{
	_isNowEnable = true;
	_camera->posX = 0;
	_camera->posY = 0;
}

static void OnKeyDown(GameObject* this, int32 vkKey)
{
	if (!_isNowEnable)
	{
		return;
	}

	switch (vkKey)
	{
		case VK_ESCAPE:
		{
			ChangeScene(SCENE_CREDIT, SCENE_MAIN_MENU);
		}
		break;

		default:
			break;
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{

}

void InitializeSceneCredit(RACamera* camera)
{
	_camera = camera;

	_sceneCredit = AllocGameObject();
	_sceneCredit->layer = LAYER_TILE;
	_sceneCredit->posX = 0;
	_sceneCredit->posY = 0;
	_sceneCredit->rotation = 0;
	_sceneCredit->scaleX = 0;
	_sceneCredit->scaleY = 0;
	_sceneCredit->isLeftDir = false;
	_sceneCredit->Start = Start;
	_sceneCredit->Update = NULL;

	_sceneCredit->animSize = 0;
	_sceneCredit->animArray = NULL;
	_sceneCredit->currAnimIndex = 0;

	SetInputCallback(_sceneCredit, OnKeyUp, OnKeyDown);

	_creditWallPaper = SetCreditWallPaper();
}

void EnableSceneCredit()
{
	EnableGameObject(_sceneCredit);
	EnableGameObject(_creditWallPaper);
}

void DisableSceneCredit()
{
	_isNowEnable = false;

	DisableGameObject(_sceneCredit);
	DisableGameObject(_creditWallPaper);
}

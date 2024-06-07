#include "SceneHowToPlay.h"
#include "RAGameEngine.h"
#include "RACamera.h"
#include "RAInput.h"
#include "RAType.h"

#include "SceneMgr.h"

#include "define.h"
#include "HowToPlayWallPaper.h"

static bool _isNowEnable = false;
static RACamera* _camera;

static GameObject* _sceneHowToPlay;

static GameObject* _HowToPlayWallPaper;

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
			ChangeScene(SCENE_HOW_TO_PLAY, SCENE_MAIN_MENU);
		}
		break;

		default:
			break;
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{

}

void InitializeSceneHowToPlay(RACamera* camera)
{
	_camera = camera;

	_sceneHowToPlay = AllocGameObject();
	_sceneHowToPlay->layer = LAYER_TILE;
	_sceneHowToPlay->posX = 0;
	_sceneHowToPlay->posY = 0;
	_sceneHowToPlay->rotation = 0;
	_sceneHowToPlay->scaleX = 0;
	_sceneHowToPlay->scaleY = 0;
	_sceneHowToPlay->isLeftDir = false;
	_sceneHowToPlay->Start = Start;
	_sceneHowToPlay->Update = NULL;

	_sceneHowToPlay->animSize = 0;
	_sceneHowToPlay->animArray = NULL;
	_sceneHowToPlay->currAnimIndex = 0;

	SetInputCallback(_sceneHowToPlay, OnKeyUp, OnKeyDown);

	_HowToPlayWallPaper = SetHowToPlayWallPaper();
}

void EnableSceneHowToPlay()
{
	EnableGameObject(_sceneHowToPlay);
	EnableGameObject(_HowToPlayWallPaper);
}

void DisableSceneHowToPlay()
{
	_isNowEnable = false;

	DisableGameObject(_sceneHowToPlay);
	DisableGameObject(_HowToPlayWallPaper);
}

#include "SceneGameClear.h"

#include "RAGameEngine.h"
#include "RACamera.h"
#include "RAInput.h"

#include "SceneMgr.h"
#include "GameClearWallPaper.h"
#include "SoundManager.h"
#include "define.h"

static GameObject* _sceneGameClear;

static bool _isNowEnable = false;
static RACamera* _camera;

static GameObject* _gameClearWallPaper;

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
			ChangeScene(SCENE_GAME_CLEAR, SCENE_MAIN_MENU);
		}
		break;

		default:
			break;
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{

}

void InitializeSceneGameClear(RACamera* camera)
{
	_camera = camera;

	_sceneGameClear = AllocGameObject();
	_sceneGameClear->layer = LAYER_TILE;
	_sceneGameClear->posX = 0;
	_sceneGameClear->posY = 0;
	_sceneGameClear->rotation = 0;
	_sceneGameClear->scaleX = 0;
	_sceneGameClear->scaleY = 0;
	_sceneGameClear->isLeftDir = false;
	_sceneGameClear->Start = Start;
	_sceneGameClear->Update = NULL;

	_sceneGameClear->animSize = 0;
	_sceneGameClear->animArray = NULL;
	_sceneGameClear->currAnimIndex = 0;

	SetInputCallback(_sceneGameClear, OnKeyUp, OnKeyDown);

	_gameClearWallPaper = SetGameClearWallPaper();
}

void EnableSceneGameClear()
{
	EnableGameObject(_sceneGameClear);
	EnableGameObject(_gameClearWallPaper);
	PlayBGMSound(ENDING_BGM);
}

void DisableSceneGameClear()
{
	_isNowEnable = false;
	DisableGameObject(_sceneGameClear);
	DisableGameObject(_gameClearWallPaper);
	StopSound(ENDING_BGM);
}



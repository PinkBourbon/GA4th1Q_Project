#include "SceneGameOver.h"

#include "RAGameEngine.h"
#include "RACamera.h"
#include "RAInput.h"

#include "SceneMgr.h"
#include "GameOverWallPaper.h"
#include "SoundManager.h"
#include "define.h"

static GameObject* _sceneGameOver;

static bool _isNowEnable = false;

static RACamera* _camera;

static GameObject* _gameOverWallPaper;

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
			ChangeScene(SCENE_GAME_OVER, SCENE_MAIN_MENU);
		}
		break;

		default:
			break;
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{

}

void InitializeSceneGameOver(RACamera* camera)
{
	_camera = camera;


	_sceneGameOver = AllocGameObject();
	_sceneGameOver->layer = LAYER_TILE;
	_sceneGameOver->posX = 0;
	_sceneGameOver->posY = 0;
	_sceneGameOver->rotation = 0;
	_sceneGameOver->scaleX = 0;
	_sceneGameOver->scaleY = 0;
	_sceneGameOver->isLeftDir = false;
	_sceneGameOver->Start = Start;
	_sceneGameOver->Update = NULL;

	_sceneGameOver->animSize = 0;
	_sceneGameOver->animArray = NULL;
	_sceneGameOver->currAnimIndex = 0;

	SetInputCallback(_sceneGameOver, OnKeyUp, OnKeyDown);

	_gameOverWallPaper = SetGameOverWallPaper();
}

void EnableSceneGameOver()
{
	EnableGameObject(_sceneGameOver);
	EnableGameObject(_gameOverWallPaper);
	PlayBGMSound(GAMEOVER_BGM);
}

void DisableSceneGameOver()
{
	_isNowEnable = false;

	DisableGameObject(_sceneGameOver);
	DisableGameObject(_gameOverWallPaper);
	StopSound(GAMEOVER_BGM);
}


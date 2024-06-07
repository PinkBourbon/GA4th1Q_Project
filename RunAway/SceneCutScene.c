#include "SceneCutScene.h"
#include "RAGameEngine.h"
#include "RACamera.h"
#include "RAInput.h"
#include "RAType.h"

#include "SceneMgr.h"

#include "define.h"
#include "CutSceneWallPaper.h"

static bool _isNowEnable = false;
static RACamera* _camera;

static GameObject* _sceneCutScene;

static GameObject* _CutSceneWallPaper;

static void Start(GameObject* this)
{
	_isNowEnable = true;
	_camera->posX = 0;
	_camera->posY = 0;
	_CutSceneWallPaper->currAnimIndex = 0;
}

static void OnKeyDown(GameObject* this, int32 vkKey)
{
	if (!_isNowEnable)
	{
		return;
	}

	switch (vkKey)
	{
		case VK_SPACE:
		{
			if (_CutSceneWallPaper->currAnimIndex >= 3)
			{
				ChangeScene(SCENE_CUT_SCENE_FIRST, SCENE_GAME_PLAY);
				StopSound(MAIN_MENU_BGM);
				return;
			}
			_CutSceneWallPaper->currAnimIndex += 1;
		}
		break;

		default:
			break;
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{

}

void InitializeSceneCutScene(RACamera* camera)
{
	_camera = camera;

	_sceneCutScene = AllocGameObject();
	_sceneCutScene->layer = LAYER_TILE;
	_sceneCutScene->posX = 0;
	_sceneCutScene->posY = 0;
	_sceneCutScene->rotation = 0;
	_sceneCutScene->scaleX = 0;
	_sceneCutScene->scaleY = 0;
	_sceneCutScene->isLeftDir = false;
	_sceneCutScene->Start = Start;
	_sceneCutScene->Update = NULL;

	_sceneCutScene->animSize = 0;
	_sceneCutScene->animArray = NULL;
	_sceneCutScene->currAnimIndex = 0;

	SetInputCallback(_sceneCutScene, OnKeyUp, OnKeyDown);

	_CutSceneWallPaper = SetCutSceneWallPaper();
}

void EnableSceneCutScene()
{
	EnableGameObject(_sceneCutScene);
	EnableGameObject(_CutSceneWallPaper);
}

void DisableSceneCutScene()
{
	_isNowEnable = false;

	DisableGameObject(_sceneCutScene);
	DisableGameObject(_CutSceneWallPaper);
}

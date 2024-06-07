#include "SceneMgr.h"
#include "RAGameEngine.h"
#include "SceneCredit.h"
#include "SceneGameClear.h"
#include "SceneGameOver.h"
#include "SceneGamePlay.h"
#include "SceneHowToPlay.h"
#include "SceneMainMenu.h"
#include "SceneCutScene.h"
#include "SoundManager.h"
#include "define.h"

typedef struct _GameObject GameObject;

GameObject* _soundMgr;

void InitializeSceneMgr(RACamera* camera)
{
	InitializeSceneCredit(camera);
	InitializeSceneGameClear(camera);
	InitializeSceneGameOver(camera);
	InitializeSceneGamePlay(camera);
	InitializeSceneHowToPlay(camera);
	InitializeSceneMainMenu(camera);
	InitializeSceneCutScene(camera);

	_soundMgr = SetSoundManager();
	EnableGameObject(_soundMgr);

	EnableSceneMainMenu();
	PlayBGMSound(MAIN_MENU_BGM);
}

void ChangeScene(eSceneState thisScene, eSceneState changeScene)
{
	switch (thisScene)
	{
		case SCENE_MAIN_MENU:
		{
			DisableSceneMainMenu();
		}
		break;

		case SCENE_CREDIT:
		{
			DisableSceneCredit();
		}
		break;

		case SCENE_HOW_TO_PLAY:
		{
			DisableSceneHowToPlay();
		}
		break;

		case SCENE_GAME_PLAY:
		{
			DisableSceneGamePlay();
		}
		break;
		      
		case SCENE_GAME_OVER:
		{

			DisableSceneGameOver();
			PlayBGMSound(MAIN_MENU_BGM);
		}
		break;

		case SCENE_GAME_CLEAR:
		{
			DisableSceneGameClear();
			PlayBGMSound(MAIN_MENU_BGM);
		}
		break;

		case SCENE_CUT_SCENE_FIRST:
		{
			DisableSceneCutScene();
		}
		break;

		case SCENE_CUT_SCENE_SECOND:
		{
			DisableSceneCutScene();
		}
		break;

		case SCENE_CUT_SCENE_THIRD:
		{
			DisableSceneCutScene();
		}
		break;

		case SCENE_CUT_SCENE_FOURTH:
		{
			DisableSceneGameClear();
		}
		break;

		default:
			break;
	}

	switch (changeScene)
	{
		case SCENE_MAIN_MENU:
		{
			EnableSceneMainMenu();
		}
		break;

		case SCENE_CREDIT:
		{
			EnableSceneCredit();
		}
		break;

		case SCENE_HOW_TO_PLAY:
		{
			EnableSceneHowToPlay();
		}
		break;

		case SCENE_GAME_PLAY:
		{
			EnableSceneGamePlay();
		}
		break;

		case SCENE_GAME_OVER:
		{
			EnableSceneGameOver();
		}
		break;

		case SCENE_GAME_CLEAR:
		{
			EnableSceneGameClear();
		}
		break;

		case SCENE_CUT_SCENE_FIRST:
		{
			EnableSceneCutScene();
		}
		break;

		case SCENE_CUT_SCENE_SECOND:
		{
			EnableSceneCutScene();
		}
		break;

		case SCENE_CUT_SCENE_THIRD:
		{
			EnableSceneCutScene();
		}
		break;

		case SCENE_CUT_SCENE_FOURTH:
		{
			EnableSceneCutScene();
		}
		break;

		default:
			break;
	}
}

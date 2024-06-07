#pragma once

typedef struct _RACamera RACamera;

typedef enum _eSceneState
{
	SCENE_MAIN_MENU,
	SCENE_CREDIT,
	SCENE_HOW_TO_PLAY,
	SCENE_GAME_PLAY,
	SCENE_GAME_OVER,
	SCENE_GAME_CLEAR,
	SCENE_CUT_SCENE_FIRST,
	SCENE_CUT_SCENE_SECOND,
	SCENE_CUT_SCENE_THIRD,
	SCENE_CUT_SCENE_FOURTH
}eSceneState;

void InitializeSceneMgr(RACamera* camera);

void ChangeScene(eSceneState thisScene, eSceneState changeScene);
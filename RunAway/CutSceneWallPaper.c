#include "CutSceneWallPaper.h"
#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"

static GameObject* _cutSceneWallPaper;

GameObject* SetCutSceneWallPaper()
{
	_cutSceneWallPaper = AllocGameObject();

	_cutSceneWallPaper->layer = LAYER_TILE;
	_cutSceneWallPaper->posX = 0;
	_cutSceneWallPaper->posY = 0;
	_cutSceneWallPaper->rotation = 0;
	_cutSceneWallPaper->scaleX = 0;
	_cutSceneWallPaper->scaleY = 0;
	_cutSceneWallPaper->isLeftDir = true;
	_cutSceneWallPaper->Start = NULL;
	_cutSceneWallPaper->Update = NULL;

	_cutSceneWallPaper->animSize = 4;
	_cutSceneWallPaper->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _cutSceneWallPaper->animSize);
	_cutSceneWallPaper->currAnimIndex = 0;

	SetAnimation(_cutSceneWallPaper->animArray, 0, 1000, 1);
	SetImage(_cutSceneWallPaper->animArray, 0, 0, FIRST_CUTSCENE_WALL_PAPER);

	SetAnimation(_cutSceneWallPaper->animArray, 1, 1000, 1);
	SetImage(_cutSceneWallPaper->animArray, 1, 0, SECOND_CUTSCENE_WALL_PAPER);
	
	SetAnimation(_cutSceneWallPaper->animArray, 2, 1000, 1);
	SetImage(_cutSceneWallPaper->animArray, 2, 0, THIRD_CUTSCENE_WALL_PAPER);

	SetAnimation(_cutSceneWallPaper->animArray, 3, 1000, 1);
	SetImage(_cutSceneWallPaper->animArray, 3, 0, FOURTH_CUTSCENE_WALL_PAPER);

	return _cutSceneWallPaper;
}

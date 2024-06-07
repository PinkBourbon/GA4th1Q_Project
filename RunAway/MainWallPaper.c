#include "MainWallPaper.h"
#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"

static GameObject* _mainWallPaper;

GameObject* SetMainWallPaper()
{
	_mainWallPaper = AllocGameObject();

	_mainWallPaper->layer = LAYER_TILE;
	_mainWallPaper->posX = 0;
	_mainWallPaper->posY = 0;
	_mainWallPaper->rotation = 0;
	_mainWallPaper->scaleX = 0;
	_mainWallPaper->scaleY = 0;
	_mainWallPaper->isLeftDir = true;
	_mainWallPaper->Start = NULL;
	_mainWallPaper->Update = NULL;

	_mainWallPaper->animSize = 1;
	_mainWallPaper->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _mainWallPaper->animSize);
	_mainWallPaper->currAnimIndex = 0;

	SetAnimation(_mainWallPaper->animArray, 0, 1000, 1);
	SetImage(_mainWallPaper->animArray, 0, 0, MAIN_MENU_WALL_PAPER);

	return _mainWallPaper;
}


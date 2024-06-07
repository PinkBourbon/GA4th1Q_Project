#include "GameMenuWallPaper.h"
#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"

static GameObject* _gameMenuWallPaper;

GameObject* SetGameMenuWallPaper()
{
	_gameMenuWallPaper = AllocGameObject();

	_gameMenuWallPaper->layer = LAYER_UI;
	_gameMenuWallPaper->posX = 0;
	_gameMenuWallPaper->posY = 0;
	_gameMenuWallPaper->rotation = 0;
	_gameMenuWallPaper->scaleX = 0;
	_gameMenuWallPaper->scaleY = 0;
	_gameMenuWallPaper->isLeftDir = true;
	_gameMenuWallPaper->Start = NULL;
	_gameMenuWallPaper->Update = NULL;

	_gameMenuWallPaper->animSize = 1;
	_gameMenuWallPaper->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _gameMenuWallPaper->animSize);
	_gameMenuWallPaper->currAnimIndex = 0;

	SetAnimation(_gameMenuWallPaper->animArray, 0, 1000, 1);
	SetImage(_gameMenuWallPaper->animArray, 0, 0, GM_MENU_WALL_PAPER);

	return _gameMenuWallPaper;
}


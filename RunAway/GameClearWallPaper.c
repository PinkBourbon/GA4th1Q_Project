#include "GameClearWallPaper.h"
#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"

static GameObject* _gameClearWallPaper;

GameObject* SetGameClearWallPaper()
{
	_gameClearWallPaper = AllocGameObject();

	_gameClearWallPaper->layer = LAYER_TILE;
	_gameClearWallPaper->posX = 0;
	_gameClearWallPaper->posY = 0;
	_gameClearWallPaper->rotation = 0;
	_gameClearWallPaper->scaleX = 0;
	_gameClearWallPaper->scaleY = 0;
	_gameClearWallPaper->isLeftDir = true;
	_gameClearWallPaper->Start = NULL;
	_gameClearWallPaper->Update = NULL;

	_gameClearWallPaper->animSize = 1;
	_gameClearWallPaper->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _gameClearWallPaper->animSize);
	_gameClearWallPaper->currAnimIndex = 0;

	SetAnimation(_gameClearWallPaper->animArray, 0, 1000, 1);
	SetImage(_gameClearWallPaper->animArray, 0, 0, GAME_CLEAR_WALL_PAPER);

	return _gameClearWallPaper;
}


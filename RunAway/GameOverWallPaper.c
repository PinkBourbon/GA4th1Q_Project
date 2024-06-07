#include "CreditWallPaper.h"
#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"

static GameObject* _gameOverWallPaper;

GameObject* SetGameOverWallPaper()
{
	_gameOverWallPaper = AllocGameObject();

	_gameOverWallPaper->layer = LAYER_TILE;
	_gameOverWallPaper->posX = 0;
	_gameOverWallPaper->posY = 0;
	_gameOverWallPaper->rotation = 0;
	_gameOverWallPaper->scaleX = 0;
	_gameOverWallPaper->scaleY = 0;
	_gameOverWallPaper->isLeftDir = true;
	_gameOverWallPaper->Start = NULL;
	_gameOverWallPaper->Update = NULL;

	_gameOverWallPaper->animSize = 1;
	_gameOverWallPaper->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _gameOverWallPaper->animSize);
	_gameOverWallPaper->currAnimIndex = 0;

	SetAnimation(_gameOverWallPaper->animArray, 0, 1000, 1);
	SetImage(_gameOverWallPaper->animArray, 0, 0, GAME_OVER_WALL_PAPER);

	return _gameOverWallPaper;
}

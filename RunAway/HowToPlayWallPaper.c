#include "HowToPlayWallPaper.h"
#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"

static GameObject* _creditWallPaper;

GameObject* SetHowToPlayWallPaper()
{
	_creditWallPaper = AllocGameObject();

	_creditWallPaper->layer = LAYER_TILE;
	_creditWallPaper->posX = 0;
	_creditWallPaper->posY = 0;
	_creditWallPaper->rotation = 0;
	_creditWallPaper->scaleX = 0;
	_creditWallPaper->scaleY = 0;
	_creditWallPaper->isLeftDir = true;
	_creditWallPaper->Start = NULL;
	_creditWallPaper->Update = NULL;

	_creditWallPaper->animSize = 1;
	_creditWallPaper->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _creditWallPaper->animSize);
	_creditWallPaper->currAnimIndex = 0;

	SetAnimation(_creditWallPaper->animArray, 0, 1000, 1);
	SetImage(_creditWallPaper->animArray, 0, 0, HOW_TO_PLAY_WALL_PAPER);

	return _creditWallPaper;
}

#include "ButtonMainMenuToGameStart.h"

#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"
static GameObject* _buttonGameStart;

GameObject* SetButtonMainMenuToGameStart()
{
	_buttonGameStart = AllocGameObject();

	_buttonGameStart->layer = LAYER_SHADOW;
	_buttonGameStart->posX = 960;
	_buttonGameStart->posY = 461;
	_buttonGameStart->rotation = 0;
	_buttonGameStart->scaleX = 0;
	_buttonGameStart->scaleY = 0;
	_buttonGameStart->isLeftDir = true;
	_buttonGameStart->Start = NULL;
	_buttonGameStart->Update = NULL;

	_buttonGameStart->animSize = 2;
	_buttonGameStart->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _buttonGameStart->animSize);
	_buttonGameStart->currAnimIndex = 1;

	SetAnimation(_buttonGameStart->animArray, 0, 1000, 1);
	SetImage(_buttonGameStart->animArray, 0, 0, M_BUTTON_GAME_START);

	SetAnimation(_buttonGameStart->animArray, 1, 1000, 1);
	SetImage(_buttonGameStart->animArray, 1, 0, M_BUTTON_GAME_START_SELECT);

	return _buttonGameStart;
}

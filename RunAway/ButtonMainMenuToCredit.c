#include "ButtonMainMenuToCredit.h"

#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"

static GameObject* _buttonCredit;

GameObject* SetButtonMainMenuToCredit()
{
	_buttonCredit = AllocGameObject();

	_buttonCredit->layer = LAYER_SHADOW;
	_buttonCredit->posX = 960;
	_buttonCredit->posY = 791;
	_buttonCredit->rotation = 0;
	_buttonCredit->scaleX = 0;
	_buttonCredit->scaleY = 0;
	_buttonCredit->isLeftDir = true;
	 _buttonCredit->Start = NULL;
	_buttonCredit->Update = NULL;

	_buttonCredit->animSize = 2;
	_buttonCredit->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _buttonCredit->animSize);
	_buttonCredit->currAnimIndex = 0;

	SetAnimation(_buttonCredit->animArray, 0, 1000, 1);
	SetImage(_buttonCredit->animArray, 0, 0, M_BUTTON_CREDIT);

	SetAnimation(_buttonCredit->animArray, 1, 1000, 1);
	SetImage(_buttonCredit->animArray, 1, 0, M_BUTTON_CREDIT_SELECT);

	return _buttonCredit;
}
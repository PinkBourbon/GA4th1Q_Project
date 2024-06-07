#include "ButtonGameOverToRestart.h"

#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"

static GameObject* _buttonRestart;

GameObject* SetButtonGameOverToRestart()
{
	_buttonRestart = AllocGameObject();

	_buttonRestart->layer = LAYER_SHADOW;
	_buttonRestart->posX = 1440;
	_buttonRestart->posY = 746;
	_buttonRestart->rotation = 0;
	_buttonRestart->scaleX = 0;
	_buttonRestart->scaleY = 0;
	_buttonRestart->isLeftDir = true;
	_buttonRestart->Start = NULL;
	_buttonRestart->Update = NULL;

	_buttonRestart->animSize = 2;
	_buttonRestart->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _buttonRestart->animSize);
	_buttonRestart->currAnimIndex = 0;

	SetAnimation(_buttonRestart->animArray, 0, 1000, 1);
	SetImage(_buttonRestart->animArray, 0, 0, "");

	SetAnimation(_buttonRestart->animArray, 1, 1000, 1);
	SetImage(_buttonRestart->animArray, 1, 0, "");

	return _buttonRestart;
}

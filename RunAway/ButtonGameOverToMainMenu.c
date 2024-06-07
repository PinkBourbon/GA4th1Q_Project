#include "ButtonGameOverToMainMenu.h"

#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"

static GameObject* _buttonMainMenu;

GameObject* SetButtonGameOverToMainMenu()
{
	_buttonMainMenu = AllocGameObject();

	_buttonMainMenu->layer = LAYER_SHADOW;
	_buttonMainMenu->posX = 480;
	_buttonMainMenu->posY = 746;
	_buttonMainMenu->rotation = 0;
	_buttonMainMenu->scaleX = 0;
	_buttonMainMenu->scaleY = 0;
	_buttonMainMenu->isLeftDir = true;
	_buttonMainMenu->Start = NULL;
	_buttonMainMenu->Update = NULL;

	_buttonMainMenu->animSize = 2;
	_buttonMainMenu->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _buttonMainMenu->animSize);
	_buttonMainMenu->currAnimIndex = 0;

	SetAnimation(_buttonMainMenu->animArray, 0, 1000, 1);
	SetImage(_buttonMainMenu->animArray, 0, 0, "");

	SetAnimation(_buttonMainMenu->animArray, 1, 1000, 1);
	SetImage(_buttonMainMenu->animArray, 1, 0, "");

	return _buttonMainMenu;
}

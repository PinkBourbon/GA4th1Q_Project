#include "ButtonMainMenuToHowToPlay.h"

#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"

static GameObject* _buttonHowToPlay;

GameObject* SetButtonMainMenuToHowToPlay()
{
	_buttonHowToPlay = AllocGameObject();

	_buttonHowToPlay->layer = LAYER_SHADOW;
	_buttonHowToPlay->posX = 960;
	_buttonHowToPlay->posY = 626;
	_buttonHowToPlay->rotation = 0;
	_buttonHowToPlay->scaleX = 0;
	_buttonHowToPlay->scaleY = 0;
	_buttonHowToPlay->isLeftDir = true;
	_buttonHowToPlay->Start = NULL;
	_buttonHowToPlay->Update = NULL;

	_buttonHowToPlay->animSize = 2;
	_buttonHowToPlay->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _buttonHowToPlay->animSize);
	_buttonHowToPlay->currAnimIndex = 0;

	SetAnimation(_buttonHowToPlay->animArray, 0, 1000, 1);
	SetImage(_buttonHowToPlay->animArray, 0, 0, M_BUTTON_HOW_TO_PLAY);

	SetAnimation(_buttonHowToPlay->animArray, 1, 1000, 1);
	SetImage(_buttonHowToPlay->animArray, 1, 0, M_BUTTON_HOW_TO_PLAY_SELECT);

	return _buttonHowToPlay;
}

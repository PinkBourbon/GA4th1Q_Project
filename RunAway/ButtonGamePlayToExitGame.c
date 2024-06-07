#include "ButtonGamePlayToExitGame.h"

#include "RAGameEngine.h"
#include "RAAnimation.h"
#include "define.h"

static GameObject* _buttonExitGame;

GameObject* SetButtonGamePlayToExitGame()
{
	_buttonExitGame = AllocGameObject();

	_buttonExitGame->layer = LAYER_UI;
	_buttonExitGame->posX = 960;
	_buttonExitGame->posY = 780;
	_buttonExitGame->rotation = 0;
	_buttonExitGame->scaleX = 0;
	_buttonExitGame->scaleY = 0;
	_buttonExitGame->isLeftDir = true;
	_buttonExitGame->Start = NULL;
	_buttonExitGame->Update = NULL;

	_buttonExitGame->animSize = 2;
	_buttonExitGame->animArray = (RAAnimation*)malloc(sizeof(RAAnimation) * _buttonExitGame->animSize);
	_buttonExitGame->currAnimIndex = 0;

	SetAnimation(_buttonExitGame->animArray, 0, 1000, 1);
	SetImage(_buttonExitGame->animArray, 0, 0, GM_BUTTON_EXIT_GAME);

	SetAnimation(_buttonExitGame->animArray, 1, 1000, 1);
	SetImage(_buttonExitGame->animArray, 1, 0, GM_BUTTON_EXIT_GAME_SELECT);

	return _buttonExitGame;
}

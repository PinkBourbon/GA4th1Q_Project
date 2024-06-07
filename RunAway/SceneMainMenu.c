#include "SceneMainMenu.h"
#include "RAGameEngine.h"
#include "RACamera.h"
#include "RAInput.h"

#include "SceneMgr.h"

#include "MainWallPaper.h"
#include "ButtonMainMenuToGameStart.h"
#include "ButtonMainMenuToHowToPlay.h"
#include "ButtonMainMenuToCredit.h"
#include "ButtonMainMenuToExitGame.h"
#include "SoundManager.h"
#include "define.h"

#define BUTTON_ARR_SIZE 4

static bool _isNowEnable = false;

static RACamera* _camera;

static GameObject* _sceneMainMenu;
static GameObject* _mainWallpaper;

static GameObject* _buttonArr[BUTTON_ARR_SIZE];



typedef enum _eSelectedMainMenuButton
{
	BUTTON_GAME_START,
	BUTTON_HOW_TO_PLAY,
	BUTTON_CREDIT,
	BUTTON_EXIT_GAME
}eSelectedMainMenuButton;

static eSelectedMainMenuButton _selectedButton = BUTTON_GAME_START;

static void SelectNextButton()
{
	_buttonArr[_selectedButton]->currAnimIndex = 0;
	_selectedButton = (_selectedButton + 1) % BUTTON_ARR_SIZE;
	_buttonArr[_selectedButton]->currAnimIndex = 1;
}

static void SelectPrevButton()
{
	_buttonArr[_selectedButton]->currAnimIndex = 0;

	_selectedButton -= 1;
	if (_selectedButton < 0)
	{
		_selectedButton = BUTTON_ARR_SIZE - 1;
	}

	_buttonArr[_selectedButton]->currAnimIndex = 1;
}

static void Start(GameObject* this)
{
	_isNowEnable = true;
	_camera->posX = 0;
	_camera->posY = 0;
}

static void OnKeyDown(GameObject* this, int32 vkKey)
{
	if (!_isNowEnable)
	{
		return;
	}

	switch (vkKey)
	{
		case VK_UP:
		{
			SelectPrevButton();
			PlayEffectSound(EFFECT_BUTTON);
		}
		break;

		case VK_DOWN:
		{
			SelectNextButton();
			PlayEffectSound(EFFECT_BUTTON);
		}
		break;

		case VK_SPACE:
		FALLTHROUGH;
		case VK_RETURN:
		FALLTHROUGH;
		case 0x46: // f Ű
		{
			switch (_selectedButton)
			{
				case BUTTON_GAME_START:
				{
					ChangeScene(SCENE_MAIN_MENU, SCENE_CUT_SCENE_FIRST);
				}
				break;
				case BUTTON_HOW_TO_PLAY:
				{
					ChangeScene(SCENE_MAIN_MENU, SCENE_HOW_TO_PLAY);
				}
				break;
				case BUTTON_CREDIT:
				{
					ChangeScene(SCENE_MAIN_MENU, SCENE_CREDIT);
				}
				break;
				case BUTTON_EXIT_GAME:
				{
					ExitGame();
				}
				break;
				default:
					break;
			}
		}
		break;

		default:
			break;
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{

}

void InitializeSceneMainMenu(RACamera* camera)
{
	_camera = camera;

	_sceneMainMenu = AllocGameObject();
	_sceneMainMenu->layer = LAYER_TILE;
	_sceneMainMenu->posX = 0;
	_sceneMainMenu->posY = 0;
	_sceneMainMenu->rotation = 0;
	_sceneMainMenu->scaleX = 0;
	_sceneMainMenu->scaleY = 0;
	_sceneMainMenu->isLeftDir = false;
	_sceneMainMenu->Start = Start;
	_sceneMainMenu->Update = NULL;

	_sceneMainMenu->animSize = 0;
	_sceneMainMenu->animArray = NULL;
	_sceneMainMenu->currAnimIndex = 0;

	SetInputCallback(_sceneMainMenu, OnKeyUp, OnKeyDown);

	_mainWallpaper = SetMainWallPaper();
	_buttonArr[0] = SetButtonMainMenuToGameStart();
	_buttonArr[1] = SetButtonMainMenuToHowToPlay();
	_buttonArr[2] = SetButtonMainMenuToCredit();
	_buttonArr[3] = SetButtonMainMenuToExitGame();
}

void EnableSceneMainMenu()
{
	EnableGameObject(_sceneMainMenu);
	EnableGameObject(_mainWallpaper);
	EnableGameObject(_buttonArr[0]);
	EnableGameObject(_buttonArr[1]);
	EnableGameObject(_buttonArr[2]);
	EnableGameObject(_buttonArr[3]);

}

void DisableSceneMainMenu()
{
	_isNowEnable = false;
	DisableGameObject(_sceneMainMenu);
	DisableGameObject(_mainWallpaper);
	DisableGameObject(_buttonArr[0]);
	DisableGameObject(_buttonArr[1]);
	DisableGameObject(_buttonArr[2]);
	DisableGameObject(_buttonArr[3]);

}

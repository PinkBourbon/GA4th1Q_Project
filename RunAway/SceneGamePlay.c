#include "SceneGamePlay.h"

#include "RAGameEngine.h"
#include "RAInput.h"
#include "RACamera.h"
#include "RAVector2.h"

#include "SceneMgr.h"
#include "Player.h"
#include "MonsterMgr.h"
#include "Monster.h"
#include "WorldMap.h"
#include "GameMenuWallPaper.h"
#include "ButtonGamePlayToMainMenu.h"
#include "ButtonGamePlayToRestart.h"
#include "ButtonGamePlayToExitGame.h"
//#include "Memo.h"
#include "StoryItem0.h"
#include "StoryItem1.h"
#include "StoryItem2.h"
#include "StoryItem3.h"
#include "StoryItem4.h"
#include "StoryItem5.h"
#include "StoryItem6.h"
#include "StoryItem7.h"
//#include "StoryItem8.h"
#include "StoryItem9.h"
#include "SoundManager.h"
#include "define.h"

#define BUTTON_ARR_SIZE 3
typedef enum _eSelectedMainMenuButton
{
	BUTTON_MAIN_MENU,
	BUTTON_RESTART_GAME,
	BUTTON_EXIT_GAME
}eSelectedMainMenuButton;

static GameObject* _buttonArr[BUTTON_ARR_SIZE];
static eSelectedMainMenuButton _selectedButton = BUTTON_MAIN_MENU;
static GameObject* _gameMenuWallPaper;

static bool _isNowEnable = false;
static bool _isGameOver = false;
static bool _isGameClear = false;

static RACamera* _camera;
static GameObject* _sceneGamePlay;
static GameObject* _player;
static GameObject* _monsterMgr;
static GameObject* _memo;
static GameObject* _storyItem0;
static GameObject* _storyItem1;
static GameObject* _storyItem2;
static GameObject* _storyItem3;
static GameObject* _storyItem4;
static GameObject* _storyItem5;
static GameObject* _storyItem6;
static GameObject* _storyItem7;
static GameObject* _storyItem8;
static GameObject* _storyItem9;

bool g_isOnMenu = false;
bool g_isPlayerViewStory = false;

static void SelectNextButton()
{
	_buttonArr[_selectedButton]->currAnimIndex = 0;
	_selectedButton = (_selectedButton + 1) % BUTTON_ARR_SIZE;
	_buttonArr[_selectedButton]->currAnimIndex = 1;
}

static void SelectPrevButton()
{
	if (_selectedButton < 0 || _selectedButton > BUTTON_ARR_SIZE)
		return;
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
	g_isOnMenu = false;
	g_isPlayerViewStory = false;
}

static void Update(GameObject* this, int64 deltaTime)
{
	if (_isGameOver)
	{
		ChangeScene(SCENE_GAME_PLAY, SCENE_GAME_OVER);
		return;
	}

	if (_isGameClear)
	{
		ChangeScene(SCENE_GAME_PLAY, SCENE_GAME_CLEAR);
		return;
	}

	if (_player->posY < 10)
	{
		GameClear();
	}
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
			if (!g_isOnMenu)
			{
				return;
			}
			SelectPrevButton();
			PlayEffectSound(EFFECT_BUTTON);
		}
		break;

		case VK_DOWN:
		{
			if (!g_isOnMenu)
			{
				return;
			}
			SelectNextButton();
			PlayEffectSound(EFFECT_BUTTON);
		}
		break;

		case VK_SPACE:
		FALLTHROUGH;
		case VK_RETURN:
		FALLTHROUGH;
		case 0x46: // f 키
		{
			if (!g_isOnMenu)
			{
				return;
			}
			switch (_selectedButton)
			{
				case BUTTON_MAIN_MENU:
				{
					ChangeScene(SCENE_GAME_PLAY, SCENE_MAIN_MENU);
					PlayBGMSound(MAIN_MENU_BGM);
				}
				break;
				case BUTTON_RESTART_GAME:
				{
					ChangeScene(SCENE_GAME_PLAY, SCENE_GAME_PLAY);
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

		case VK_ESCAPE:
		{
			g_isOnMenu = !g_isOnMenu;
			if (!g_isOnMenu)
			{
				DisableGameObject(_gameMenuWallPaper);
				DisableGameObject(_buttonArr[0]);
				DisableGameObject(_buttonArr[1]);
				DisableGameObject(_buttonArr[2]);
				return;
			}

			_selectedButton = BUTTON_MAIN_MENU;
			_gameMenuWallPaper->posX = (float)_camera->posX;
			_gameMenuWallPaper->posY = (float)_camera->posY;

			_buttonArr[0]->posX = _gameMenuWallPaper->posX + 960;
			_buttonArr[0]->posY = _gameMenuWallPaper->posY + 348;
			_buttonArr[0]->currAnimIndex = 1;

			_buttonArr[1]->posX = _gameMenuWallPaper->posX + 960;
			_buttonArr[1]->posY = _gameMenuWallPaper->posY + 564;
			_buttonArr[1]->currAnimIndex = 0;

			_buttonArr[2]->posX = _gameMenuWallPaper->posX + 960;
			_buttonArr[2]->posY = _gameMenuWallPaper->posY + 780;
			_buttonArr[2]->currAnimIndex = 0;

			EnableGameObject(_gameMenuWallPaper);
			EnableGameObject(_buttonArr[0]);
			EnableGameObject(_buttonArr[1]);
			EnableGameObject(_buttonArr[2]);
			//메뉴창을 보여주게, 다른 플레이어 조작 멈추게
		}
		break;

		default:
			break;
	}
}

static void OnKeyUp(GameObject* this, int32 vkKey)
{

}

void InitializeSceneGamePlay(RACamera* camera)
{
	Map* map = SetWorldMap();
	_camera = camera;

	_sceneGamePlay = AllocGameObject();
	_sceneGamePlay->layer = LAYER_TILE;
	_sceneGamePlay->posX = 0;
	_sceneGamePlay->posY = 0;
	_sceneGamePlay->rotation = 0;
	_sceneGamePlay->scaleX = 0;
	_sceneGamePlay->scaleY = 0;
	_sceneGamePlay->isLeftDir = false;
	_sceneGamePlay->Start = Start;
	_sceneGamePlay->Update = Update;

	_sceneGamePlay->animSize = 0;
	_sceneGamePlay->animArray = NULL;
	_sceneGamePlay->currAnimIndex = 0;

	SetInputCallback(_sceneGamePlay, OnKeyUp, OnKeyDown);

	GameObject* outOfBody = NULL;
	_player = SetPlayer(camera, map, outOfBody);
	_monsterMgr = SetMonsterMgr(_player, map);
	//_memo = SetMemo(_player, _camera);
	_storyItem0 = SetStoryItem0(_player, _camera);
	_storyItem1 = SetStoryItem1(_player, _camera);
	_storyItem2 = SetStoryItem2(_player, _camera);
	_storyItem3 = SetStoryItem3(_player, _camera);
	_storyItem4 = SetStoryItem4(_player, _camera);
	_storyItem5 = SetStoryItem5(_player, _camera);
	_storyItem6 = SetStoryItem6(_player, _camera);
	_storyItem7 = SetStoryItem7(_player, _camera);
	//_storyItem8 = SetStoryItem8(_player, _camera);
	_storyItem9 = SetStoryItem9(_player, _camera);

	_gameMenuWallPaper = SetGameMenuWallPaper();
	_buttonArr[0] = SetButtonGamePlayToMainMenu();
	_buttonArr[1] = SetButtonGamePlayToRestart();
	_buttonArr[2] = SetButtonGamePlayToExitGame();
}

void EnableSceneGamePlay()
{
	EnableGameObject(_sceneGamePlay);
	EnableGameObject(_player);
	EnableGameObject(_monsterMgr);
	//EnableGameObject(_memo);

	EnableGameObject(_storyItem0);
	EnableGameObject(_storyItem1);
	EnableGameObject(_storyItem2);
	EnableGameObject(_storyItem3);
	EnableGameObject(_storyItem4);
	EnableGameObject(_storyItem5);
	EnableGameObject(_storyItem6);
	EnableGameObject(_storyItem7);
	//EnableGameObject(_storyItem8);
	EnableGameObject(_storyItem9);


	PlayBGMSound(INGAME_BGM);
	EnableWorldMap();

	_isGameOver = false;
	_isGameClear = false;
}

void DisableSceneGamePlay()
{
	_isNowEnable = false;
	DisableGameObject(_sceneGamePlay);
	DisablePlayer();
	DisableMonsterMgr();
	//DisableMemo();

	DisableStoryItem0(_player, _camera);
	DisableStoryItem1(_player, _camera);
	DisableStoryItem2(_player, _camera);
	DisableStoryItem3(_player, _camera);
	DisableStoryItem4(_player, _camera);
	DisableStoryItem5(_player, _camera);
	DisableStoryItem6(_player, _camera);
	DisableStoryItem7(_player, _camera);
	//DisableStoryItem8(_player, _camera);
	DisableStoryItem9(_player, _camera);

	StopSound(INGAME_BGM);
	DisableWorldMap();

	if (g_isOnMenu)
	{
		DisableGameObject(_gameMenuWallPaper);
		DisableGameObject(_buttonArr[0]);
		DisableGameObject(_buttonArr[1]);
		DisableGameObject(_buttonArr[2]);
	}
	g_isOnMenu = false;
}

void GameOver()
{
	_isGameOver = true;
}

void GameClear()
{
	_isGameClear = true;
}

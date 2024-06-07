#pragma once

/// render용 레이어
#define LAYER_TILE 0
#define LAYER_SHADOW 1
#define LAYER_COMMON_OBJECT 2
#define LAYER_TEMP 3
#define LAYER_MONSTER 4
#define LAYER_TEMP2 5
#define LAYER_UI 6

/// 이미지 경로
//플레이어 이미지
#define PLAYER_IDLE_0 ".\\Image\\Player\\Character_Front_1_a.bmp"
#define PLAYER_FRONT_0 ".\\Image\\Player\\Character_Front_1_a.bmp"
#define PLAYER_FRONT_1 ".\\Image\\Player\\Character_Front_2_a.bmp"
#define PLAYER_FRONT_2 ".\\Image\\Player\\Character_Front_3_a.bmp"
#define PLAYER_FRONT_3 ".\\Image\\Player\\Character_Front_4_a.bmp"
#define PLAYER_REAR_0 ".\\Image\\Player\\Character_Rear_1_a.bmp"
#define PLAYER_REAR_1 ".\\Image\\Player\\Character_Rear_2_a.bmp"
#define PLAYER_REAR_2 ".\\Image\\Player\\Character_Rear_3_a.bmp"
#define PLAYER_REAR_3 ".\\Image\\Player\\Character_Rear_4_a.bmp"

// 유체이탈 이미지
#define PLAYER_SOUL_FRONT_0 ".\\Image\\Player\\Character_Soul_Brother_Front_1_a.bmp"
#define PLAYER_SOUL_FRONT_1 ".\\Image\\Player\\Character_Soul_Brother_Front_2_a.bmp"
#define PLAYER_SOUL_REAR_0 ".\\Image\\Player\\Character_Soul_Brother_Rear_1_a.bmp"
#define PLAYER_SOUL_REAR_1 ".\\Image\\Player\\Character_Soul_Brother_Rear_2_a.bmp"

// 빛 마스크
#define LIGHT_MASK ".\\Image\\Player\\LightMask_a.bmp"
#define LIGHT_OFF_MASK ".\\Image\\Player\\LightMaskOff_a.bmp"
#define SCREENLIGHT_B ".\\Image\\Player\\Screen Light_B_a.bmp"
#define SCREENLIGHT_S ".\\Image\\Player\\Screen Light_S_a.bmp"

// 적 이미지
#define GHOST_MONSTER_FRONT_0 ".\\Image\\Enemy\\Ghost Monster_Front_1_a.bmp" 
#define GHOST_MONSTER_FRONT_1 ".\\Image\\Enemy\\Ghost Monster_Front_2_a.bmp" 
#define GHOST_MONSTER_FRONT_2 ".\\Image\\Enemy\\Ghost Monster_Front_3_a.bmp" 
#define GHOST_MONSTER_FRONT_3 ".\\Image\\Enemy\\Ghost Monster_Front_4_a.bmp" 
#define GHOST_MONSTER_REAR_0 ".\\Image\\Enemy\\Ghost Monster_Rear_1_a.bmp" 
#define GHOST_MONSTER_REAR_1 ".\\Image\\Enemy\\Ghost Monster_Rear_2_a.bmp" 
#define GHOST_MONSTER_REAR_2 ".\\Image\\Enemy\\Ghost Monster_Rear_3_a.bmp" 
#define GHOST_MONSTER_REAR_3 ".\\Image\\Enemy\\Ghost Monster_Rear_4_a.bmp" 

// 적 이미지2
#define SHADOW_MONSTER_FRONT_0 ".\\Image\\Enemy\\Shadow Monster_Front_1_a.bmp" 
#define SHADOW_MONSTER_FRONT_1 ".\\Image\\Enemy\\Shadow Monster_Front_2_a.bmp" 
#define SHADOW_MONSTER_FRONT_2 ".\\Image\\Enemy\\Shadow Monster_Front_3_a.bmp" 
#define SHADOW_MONSTER_FRONT_SIDE_0 ".\\Image\\Enemy\\Shadow Monster_Front_Side_1_a.bmp" 
#define SHADOW_MONSTER_FRONT_SIDE_1 ".\\Image\\Enemy\\Shadow Monster_Front_Side_2_a.bmp" 
#define SHADOW_MONSTER_FRONT_SIDE_2 ".\\Image\\Enemy\\Shadow Monster_Front_Side_3_a.bmp" 
#define SHADOW_MONSTER_REAR_0 ".\\Image\\Enemy\\Shadow Monster_Rear_1_a.bmp" 
#define SHADOW_MONSTER_REAR_1 ".\\Image\\Enemy\\Shadow Monster_Rear_2_a.bmp" 
#define SHADOW_MONSTER_REAR_2 ".\\Image\\Enemy\\Shadow Monster_Rear_3_a.bmp" 
#define SHADOW_MONSTER_REAR_SIDE_0 ".\\Image\\Enemy\\Shadow Monster_Rear_Side_1_a.bmp" 
#define SHADOW_MONSTER_REAR_SIDE_1 ".\\Image\\Enemy\\Shadow Monster_Rear_Side_2_a.bmp" 
#define SHADOW_MONSTER_REAR_SIDE_2 ".\\Image\\Enemy\\Shadow Monster_Rear_Side_3_a.bmp" 

// 메인메뉴 버튼
#define M_BUTTON_GAME_START ".\\Image\\UI\\MainMenu\\GameStart_a.bmp"
#define M_BUTTON_GAME_START_SELECT ".\\Image\\UI\\MainMenu\\GameStart_Click_a.bmp"
#define M_BUTTON_HOW_TO_PLAY ".\\Image\\UI\\MainMenu\\Control_a.bmp"
#define M_BUTTON_HOW_TO_PLAY_SELECT ".\\Image\\UI\\MainMenu\\Control_Click_a.bmp"
#define M_BUTTON_CREDIT ".\\Image\\UI\\MainMenu\\Credit_a.bmp"
#define M_BUTTON_CREDIT_SELECT ".\\Image\\UI\\MainMenu\\Credit_Click_a.bmp"
#define M_BUTTON_EXIT_GAME ".\\Image\\UI\\MainMenu\\Off_a.bmp"
#define M_BUTTON_EXIT_GAME_SELECT ".\\Image\\UI\\MainMenu\\Off_Click_a.bmp"

// 인게임 메뉴 관련
#define GM_BUTTON_RESTART ".\\Image\\UI\\GamePlayMenu\\Replay_a.bmp"
#define GM_BUTTON_RESTART_SELECT ".\\Image\\UI\\GamePlayMenu\\Replay_Click_a.bmp"
#define GM_BUTTON_EXIT_GAME ".\\Image\\UI\\GamePlayMenu\\Exit_a.bmp"
#define GM_BUTTON_EXIT_GAME_SELECT ".\\Image\\UI\\GamePlayMenu\\Exit_Click_a.bmp"
#define GM_BUTTON_MAIN_MENU ".\\Image\\UI\\GamePlayMenu\\MainMenu_a.bmp"
#define GM_BUTTON_MAIN_MENU_SELECT ".\\Image\\UI\\GamePlayMenu\\MainMenu_Click_a.bmp"
#define GM_MENU_WALL_PAPER ".\\Image\\UI\\GamePlayMenu\\MenuBackground_a.bmp"

// 맵 정보데이터
#define MAP_DATA ".\\Image\\Maze\\Test_Maze.bmp"

// 지형 데이터
#define WALL_0 ".\\Image\\Map\\bush02_a.bmp"
#define WALL_1 ".\\Image\\Map\\Door_a.bmp"

#define TILE_0 ".\\Image\\Map\\Ground01_a.bmp"

#define TREE_0 ".\\Image\\Map\\tree04_bush_invert_a.bmp"
#define TREE_1 ".\\Image\\Map\\tree04_bush_a.bmp"
#define TREE_2 ".\\Image\\Map\\tree05_04_bush_a.bmp"
#define TREE_3 ".\\Image\\Map\\tree05_02_bush_a.bmp"
#define TREE_4 ".\\Image\\Map\\tree01_a.bmp"

// 메뉴 배경 데이터
#define MAIN_MENU_WALL_PAPER ".\\Image\\Wallpaper\\Main Title_a.bmp"
#define HOW_TO_PLAY_WALL_PAPER ".\\Image\\Wallpaper\\HowToPlayWallPaper_a.bmp"
#define CREDIT_WALL_PAPER ".\\Image\\Wallpaper\\CreditWallPaper_a.bmp"
#define GAME_OVER_WALL_PAPER ".\\Image\\Wallpaper\\GameOver_a.bmp"
#define GAME_CLEAR_WALL_PAPER ".\\Image\\Wallpaper\\Scenes_5_a.bmp"
#define FIRST_CUTSCENE_WALL_PAPER ".\\Image\\Wallpaper\\CutScenes_1_a.bmp"
#define SECOND_CUTSCENE_WALL_PAPER ".\\Image\\Wallpaper\\CutScenes_2_a.bmp"
#define THIRD_CUTSCENE_WALL_PAPER ".\\Image\\Wallpaper\\CutScenes_3_a.bmp"
#define FOURTH_CUTSCENE_WALL_PAPER ".\\Image\\Wallpaper\\CutScenes_4_a.bmp"

#define MEMO_WALL_PAPER ".\\Image\\Wallpaper\\MemoWallPaper_a.bmp"

#define STORY_WALL_PAPER_0 ".\\Image\\StoryWallpaper\\Story_Text_01_a.bmp"
#define STORY_WALL_PAPER_1 ".\\Image\\StoryWallpaper\\Story_Text_02_a.bmp"
#define STORY_WALL_PAPER_2 ".\\Image\\StoryWallpaper\\Story_Text_03_a.bmp"
#define STORY_WALL_PAPER_3 ".\\Image\\StoryWallpaper\\Story_Text_04_a.bmp"
#define STORY_WALL_PAPER_4 ".\\Image\\StoryWallpaper\\Story_Text_05_a.bmp"
#define STORY_WALL_PAPER_5 ".\\Image\\StoryWallpaper\\Story_Text_06_a.bmp"
#define STORY_WALL_PAPER_6 ".\\Image\\StoryWallpaper\\Story_Text_07_a.bmp"
#define STORY_WALL_PAPER_7 ".\\Image\\StoryWallpaper\\Story_Text_08_a.bmp"
#define STORY_WALL_PAPER_8 ".\\Image\\StoryWallpaper\\Story_Text_09_a.bmp"
#define STORY_WALL_PAPER_9 ".\\Image\\StoryWallpaper\\Story_Text_10_a.bmp"

// 아이템 데이터
#define MEMO_ITEM_0 ".\\Image\\Item\\skull2_a.bmp"
#define MEMO_ITEM_1 ".\\Image\\Item\\skull_a.bmp"

#define STORY_0_ITEM_0 ".\\Image\\Item\\message_a.bmp"
#define STORY_0_ITEM_1 ".\\Image\\None_a.bmp"
#define STORY_1_ITEM_0 ".\\Image\\Item\\rock_4_a.bmp"
#define STORY_1_ITEM_1 ".\\Image\\None_a.bmp"
#define STORY_2_ITEM_0 ".\\Image\\Item\\message_a.bmp"
#define STORY_2_ITEM_1 ".\\Image\\None_a.bmp"
#define STORY_3_ITEM_0 ".\\Image\\Item\\message_a.bmp"
#define STORY_3_ITEM_1 ".\\Image\\None_a.bmp"
#define STORY_4_ITEM_0 ".\\Image\\Item\\rock_4_a.bmp"
#define STORY_4_ITEM_1 ".\\Image\\None_a.bmp"
#define STORY_5_ITEM_0 ".\\Image\\Item\\message_a.bmp"
#define STORY_5_ITEM_1 ".\\Image\\None_a.bmp"
#define STORY_6_ITEM_0 ".\\Image\\Item\\rock_3_a.bmp"
#define STORY_6_ITEM_1 ".\\Image\\None_a.bmp"
#define STORY_7_ITEM_0 ".\\Image\\Item\\message_a.bmp"
#define STORY_7_ITEM_1 ".\\Image\\None_a.bmp"
#define STORY_8_ITEM_0 ".\\Image\\Item\\message_a.bmp"
#define STORY_8_ITEM_1 ".\\Image\\None_a.bmp"
#define STORY_9_ITEM_0 ".\\Image\\Item\\rock_4_a.bmp"
#define STORY_9_ITEM_1 ".\\Image\\None_a.bmp"

//버그 회피등을 위한 투명 이미지
#define NO_VISUAL_IMAGE ".\\Image\\None_a.bmp"

/// 사운드 경로
#define SOUND_INTRO_BGM "..\\Sound\\BGM\\BG_G_intro_Mixing.wav"
#define SOUND_INGAME_BGM "..\\Sound\\BGM\\BG_G_ingame.wav"
#define SOUND_ENDING_BGM "..\\Sound\\BGM\\BG_G_Ending.wav"
#define SOUND_GAMEOVER_BGM "..\\Sound\\BGM\\BG_G_Gameover.wav"

#define SOUND_EFFECT_WALK "..\\sound\\Effect\\EF_Foot_Two.wav"
#define SOUND_EFFECT_WIND "..\\sound\\Effect\\EF_BG_Wind.wav"
#define SOUND_EFFECT_OWL "..\\sound\\Effect\\EF_BG_Owl.wav"
#define SOUND_EFFECT_BUTTON "..\\sound\\Effect\\EF_Button.wav"
#define SOUND_EFFECT_DROP "..\\sound\\Effect\\EF_Drop.wav"
#define SOUND_EFFECT_HEART_BEET "..\\sound\\Effect\\EF_Heart Beat_Normal.wav"
#define SOUND_EFFECT_HEART_BEET_FAST "..\\sound\\Effect\\EF_Heart Beat_Fast.wav"
#define SOUND_EFFECT_GHOST_SHOWUP "..\\sound\\Effect\\EF_Monster_Ghost_Showup.wav"
#define SOUND_EFFECT_GHOST_CATCH "..\\sound\\Effect\\EF_Monster_Ghost_PlayerCatch.wav"
#define SOUND_EFFECT_MIMIC_SHOWUP "..\\sound\\Effect\\EF_Monster_Mimic_Showup.wav"
#define SOUND_EFFECT_SHADOW_SHOWUP "..\\sound\\Effect\\EF_Monster_Shadow_Showup.wav"
#define SOUND_EFFECT_SHADOW_SHOWUP_BEFORE "..\\sound\\Effect\\EF_Monster_Shadow_Showup_Before.wav"
#define SOUND_EFFECT_SHADOW_CATCH "..\\sound\\Effect\\EF_Monster_Shadow_PlayerCatch.wav"
#define SOUND_EFFECT_STORY_TRIGGER "..\\sound\\Effect\\EF_Triger_Story_H2_Bird Fly.wav"


#define MAIN_MENU_BGM 0
#define INGAME_BGM 1
#define ENDING_BGM 2
#define GAMEOVER_BGM 3

#define EFFECT_WALK 5
#define EFFECT_WIND 6
#define EFFECT_OWL 7
#define EFFECT_BUTTON 8
#define EFFECT_DROP 9
#define EFFECT_HEART_BEET 10
#define EFFECT_HEART_BEET_FAST 11
#define EFFECT_GHOST_SHOWUP 12
#define EFFECT_GHOST_CATCH 13
#define EFFECT_MIMIC_SHOWUP 14
#define EFFECT_SHADOW_SHOWUP 15
#define EFFECT_SHADOW_SHOWUP_BEFORE 16
#define EFFECT_SHADOW_CATCH 17
#define EFFECT_STORY_TRIGGER 18
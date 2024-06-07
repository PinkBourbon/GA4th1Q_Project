
#include <stdio.h>
#include <windows.h>
#include <fmod.h>

#include "RAInput.h"
#include "RAGameObject.h"
#include "RASingleList.h"
#include "RAGameEngine.h"

#include "RAType.h"

#pragma comment(lib, "RunAwayEngine.lib")
#pragma comment(lib, "fmod_vc.lib")

// // 사운드 시스템 포인터 변수
// // (FMOD 시스템을 쓰기위해 하는건가?? 사실 잘 모르겠다. 이렇게 쓰더라..)
// FMOD_SYSTEM* g_System = NULL;
// // 사운드 객체 포인터 변수(배열에 사운드파일 저장)
// FMOD_SOUND* g_Sound[10];
// // 사운드 출력하는 채널(동시 출력할때 사용)
// FMOD_CHANNEL* g_Channel[10];
// 
// void SoundSystemInput()
// {
// 	FMOD_System_Create(&g_System, 2.02);
// 	FMOD_System_Init(g_System, 64, FMOD_INIT_NORMAL, NULL);
// }
// 
// void InputSoundFile()
// {
// 	FMOD_System_CreateSound(g_System, TEST1, FMOD_LOOP_NORMAL, 0, g_Sound[0]);
// 	FMOD_System_CreateSound(g_System, TEST2, FMOD_DEFAULT, 0, g_Sound[1]);
// }
// 
// void PlaySoundFile()
// {
// 	FMOD_System_PlaySound(g_System, g_Sound[0], NULL, 0, &g_Channel[0]);
// 	FMOD_System_PlaySound(g_System, g_Sound[1], NULL, 0, &g_Channel[1]);
// }

int main()
{

	int i = 0;
	CreateSoundSystem();
	void* bgm;
	LoadBGM("singing.wav", &bgm);
	PlayBGM(bgm);


	//InputSoundFile();
	//PlaySoundFile();
	printf("hello world\n");
	while (true)
	{
		Sleep(100);

		scanf_s("%d", &i);

		switch (i)
		{
		case 1:
			PausedSound();
			break;
		case 2:
			SoundStop(1);
			break;
		case 3:
			DestroySound();
			CreateSoundSystem();
			break;
		case 4:
			LoadBGM("singing.wav", &bgm);
			PlayBGM(bgm);
			break;
		case 5:
			BGMVolumeUp();
			break;
		case 6:
			BGMVolumeDown();
			break;
		default:
			break;
		}
	}
}

// void MyUpdate(GameObject* this, int64 deltatime);
// 
// void MyStart(GameObject* this)
// {
// 	printf("Start의 호출 내 아이디는 %d\n", this->gameObjectID);
// 
// 	GameObject* gameObject = AllocGameObject();
// 	gameObject->Start = MyStart;
// 	gameObject->Update = MyUpdate;
// 	EnableGameObject(gameObject);
// }
// 
// void MyUpdate(GameObject* this, int64 deltatime)
// {
// 	printf("\tUpdate, Id : %d, Delta : %lld\n", this->gameObjectID, deltatime);
// 	Sleep(100);
// }
// 
// int main()
// {
// 	InitializeEngine(NULL);
// 
// 	GameObject* gameObject = AllocGameObject();
// 	gameObject->Start = MyStart;
// 	gameObject->Update = MyUpdate;
// 
// 	EnableGameObject(gameObject);
// 
// 
// 
// 	GameLoop();

	//for (int i = 0 ; i < 10000; ++i)
	//{
	//	for (int j = 0; j < 10; ++j)
	//	{
	//		if (GetAsyncKeyState(VK_LEFT)& 0x8001)
	//		{
	//			printf("LEFT PRESS\n");
	//		}
	//		else
	//		{
	//			printf("LEFT UNPRESS\n");
	//		}
	//		Sleep(500);
	//	}
	//	if (GetAsyncKeyState(VK_RIGHT)&0x8000)
	//	{
	//		printf("RIGHT PRESS\n");
	//	}
	//	else
	//	{
	//		printf("RIGHT UNPRESS\n");
	//	}
	//	Sleep(500);
	//	system("cls");
	//}
// }
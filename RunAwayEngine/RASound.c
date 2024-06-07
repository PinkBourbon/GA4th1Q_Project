#include <conio.h>
#include <fmod.h>
#include "RASound.h"
#include "RAType.h"

#define MAX_SOUND 20

// 사운드 시스템 포인터 변수
// (FMOD 시스템을 쓰기위해 하는건가?? 사실 잘 모르겠다. 이렇게 쓰더라..)
FMOD_SYSTEM* g_System = NULL;
// 사운드 객체 포인터 변수(배열에 사운드파일 저장)
FMOD_SOUND* g_Sound[MAX_SOUND];
// 사운드 출력하는 채널(동시 출력할때 사용)
FMOD_CHANNEL* g_Channel[MAX_SOUND];
// 일시정지 상태 판단
FMOD_BOOL isPaused = 0;
// 볼륨값 선언
float BgmVolume = 1.0f;
float EffectVolume = 1.0f;

// 사운드 시스템 생성
// 한번만 호출할 것!!
void CreateSoundSystem()
{
	FMOD_System_Create(&g_System, FMOD_VERSION);
	// 시스템 초기화
	FMOD_System_Init(g_System, 64, FMOD_INIT_NORMAL, NULL);
}

// 사운드 파일을 저장
// FMOD_DEFAULT -> 1번 출력
// FMOD_LOOP_NORMAL -> 반복 출력

void LoadBGM(const char* filePath, void** bgmSound, int num)
{
	FMOD_System_CreateSound(g_System, filePath, FMOD_LOOP_NORMAL, 0, &(g_Sound[num]));

	bgmSound = &(g_Sound[num]);
}

void PlayBGM(int num)
{
	FMOD_System_PlaySound(g_System, g_Sound[num], NULL, isPaused, &(g_Channel[num]));
}

void LoadEffect(const char* filePath, void** bgmSound, int num)
{
	FMOD_System_CreateSound(g_System, filePath, FMOD_LOOP_NORMAL, 0, &(g_Sound[num]));
}

void LoadEffectOnce(const char* filePath, void** bgmSound, int num)
{
	FMOD_System_CreateSound(g_System, filePath, FMOD_DEFAULT, 0, &(g_Sound[num]));
}

void PlayEffect(int num)
{
	FMOD_System_PlaySound(g_System, g_Sound[num], NULL, isPaused, &(g_Channel[num]));
}


// 사운드 출력 일시정지
void PausedSound()
{
	for (int i = 0; i < MAX_SOUND; i++)
	{
	isPaused = !isPaused;
	FMOD_Channel_SetPaused(g_Channel[i], isPaused);
	}
}

// 사운드 출력 정지
void SoundStop(int ChNumber)
{
	FMOD_Channel_Stop(g_Channel[ChNumber]);
}

// 사운드 출력 전부 정지
void SoundAllStop()
{
	for (int i = 0; i < MAX_SOUND; i++)
	{
		FMOD_Channel_Stop(g_Channel[i]);
	}
}

// 사운드 업데이트(프레임 단위로 호출)
void UpdateSound()
{
	FMOD_System_Update(g_System);
}

// 사운드 시스템 해제
void DestroySound()
{
	//실제로 Sound 어레이에 10개가 모두 들어있지 않은 상태에서 Release를 시도한다면
	//더블 free등 문제가 생길 여지가 다분한 코드. 반드시 수정해야한다.
	for (int i = 0; i < MAX_SOUND; ++i)
	{
		FMOD_Sound_Release(g_Sound[i]);
	}
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

// 볼륨 세팅
void SetBGMVolume(int ChNum)
{
	FMOD_Channel_SetVolume(g_Channel[ChNum], BgmVolume);
}

void BGMVolumeUp()
{
	BgmVolume += 0.1f;

	if (BgmVolume >= 1.0f)
	{
		BgmVolume = 1.0f;
	}
	FMOD_Channel_SetVolume(g_Channel[0], BgmVolume);
}


void BGMVolumeDown()
{
	BgmVolume -= 0.1f;

	if (BgmVolume <= 0.0f)
	{
		BgmVolume = 0.0f;
	}
	FMOD_Channel_SetVolume(g_Channel[0], BgmVolume);
}

void SetEffectVolume(int ChNum)
{
	FMOD_Channel_SetVolume(g_Channel[ChNum], EffectVolume);
}

void EffectVolumeUp()
{
	EffectVolume += 0.1f;

	if (EffectVolume >= 1.0f)
	{
		EffectVolume = 1.0f;
	}
	FMOD_Channel_SetVolume(g_Channel[0], EffectVolume);
}

void EffectVolumeDown()
{
	EffectVolume -= 0.1f;

	if (EffectVolume <= 0.0f)
	{
		EffectVolume = 0.0f;
	}
	FMOD_Channel_SetVolume(g_Channel[0], EffectVolume);
}

// 얘네를 가지고 한번 놀아보자~
// 상대경로는 사회 악이다.(..\ <- 죽어!!!!!)




// 생각을 해보자...
// 음악파일은 총 두가지이다.
// bgm, effect
// 그렇다면 bgm, effect 각각 모두 로드를 한 다음
// 필요한 상황에 맞춰서 쓸 수 있도록 해주면 되는거 아닌가???
// fmod를 사용해서 로드, 재생, 일시정지, 정지, 볼륨 업,다운, 만들었는데...
// 이걸 어떻게 써먹어야할까.... 어디까지 포인터를 써서 불러오고...
// 어디는 그냥 함수내부에서 쓸 수 있도록 해야할까???
// 
// 음원 파일을 어디에 선언해둔다고 했었지??? 이거 물어보고
// 선언해둔 곳을 바탕으로 어떻게 할지 생각을 해보자...
// 전부다 디파인을 해서 enum으로 돌려버릴까?
// 어떻게 해버릴까...

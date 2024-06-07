#include <conio.h>
#include <fmod.h>
#include "RASound.h"
#include "RAType.h"

#define MAX_SOUND 20

// ���� �ý��� ������ ����
// (FMOD �ý����� �������� �ϴ°ǰ�?? ��� �� �𸣰ڴ�. �̷��� ������..)
FMOD_SYSTEM* g_System = NULL;
// ���� ��ü ������ ����(�迭�� �������� ����)
FMOD_SOUND* g_Sound[MAX_SOUND];
// ���� ����ϴ� ä��(���� ����Ҷ� ���)
FMOD_CHANNEL* g_Channel[MAX_SOUND];
// �Ͻ����� ���� �Ǵ�
FMOD_BOOL isPaused = 0;
// ������ ����
float BgmVolume = 1.0f;
float EffectVolume = 1.0f;

// ���� �ý��� ����
// �ѹ��� ȣ���� ��!!
void CreateSoundSystem()
{
	FMOD_System_Create(&g_System, FMOD_VERSION);
	// �ý��� �ʱ�ȭ
	FMOD_System_Init(g_System, 64, FMOD_INIT_NORMAL, NULL);
}

// ���� ������ ����
// FMOD_DEFAULT -> 1�� ���
// FMOD_LOOP_NORMAL -> �ݺ� ���

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


// ���� ��� �Ͻ�����
void PausedSound()
{
	for (int i = 0; i < MAX_SOUND; i++)
	{
	isPaused = !isPaused;
	FMOD_Channel_SetPaused(g_Channel[i], isPaused);
	}
}

// ���� ��� ����
void SoundStop(int ChNumber)
{
	FMOD_Channel_Stop(g_Channel[ChNumber]);
}

// ���� ��� ���� ����
void SoundAllStop()
{
	for (int i = 0; i < MAX_SOUND; i++)
	{
		FMOD_Channel_Stop(g_Channel[i]);
	}
}

// ���� ������Ʈ(������ ������ ȣ��)
void UpdateSound()
{
	FMOD_System_Update(g_System);
}

// ���� �ý��� ����
void DestroySound()
{
	//������ Sound ��̿� 10���� ��� ������� ���� ���¿��� Release�� �õ��Ѵٸ�
	//���� free�� ������ ���� ������ �ٺ��� �ڵ�. �ݵ�� �����ؾ��Ѵ�.
	for (int i = 0; i < MAX_SOUND; ++i)
	{
		FMOD_Sound_Release(g_Sound[i]);
	}
	FMOD_System_Close(g_System);
	FMOD_System_Release(g_System);
}

// ���� ����
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

// ��׸� ������ �ѹ� ��ƺ���~
// ����δ� ��ȸ ���̴�.(..\ <- �׾�!!!!!)




// ������ �غ���...
// ���������� �� �ΰ����̴�.
// bgm, effect
// �׷��ٸ� bgm, effect ���� ��� �ε带 �� ����
// �ʿ��� ��Ȳ�� ���缭 �� �� �ֵ��� ���ָ� �Ǵ°� �ƴѰ�???
// fmod�� ����ؼ� �ε�, ���, �Ͻ�����, ����, ���� ��,�ٿ�, ������µ�...
// �̰� ��� ��Ծ���ұ�.... ������ �����͸� �Ἥ �ҷ�����...
// ���� �׳� �Լ����ο��� �� �� �ֵ��� �ؾ��ұ�???
// 
// ���� ������ ��� �����صдٰ� �߾���??? �̰� �����
// �����ص� ���� �������� ��� ���� ������ �غ���...
// ���δ� �������� �ؼ� enum���� ����������?
// ��� �ع�����...

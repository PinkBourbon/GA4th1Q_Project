#include "SoundManager.h"
#include "RAGameEngine.h"
#include "RASound.h"
#include "RAInput.h"


#include "define.h"


GameObject* _SoundManager;

static void LoadBGMSound()
{
	void* bgm;
	LoadBGM(SOUND_INTRO_BGM, &bgm, 0);
	LoadBGM(SOUND_INGAME_BGM, &bgm, 1);
	LoadBGM(SOUND_ENDING_BGM, &bgm, 2);
	LoadBGM(SOUND_GAMEOVER_BGM, &bgm, 3);
}

static void LoadEffectSound()
{
	void* effect;
	LoadEffect(SOUND_EFFECT_WALK, &effect, 5);
	LoadEffect(SOUND_EFFECT_WIND, &effect, 6);
	LoadEffect(SOUND_EFFECT_OWL, &effect, 7);
	LoadEffectOnce(SOUND_EFFECT_BUTTON, &effect, 8);
	LoadEffect(SOUND_EFFECT_DROP, &effect, 9);
	LoadEffect(SOUND_EFFECT_HEART_BEET, &effect, 10);
	LoadEffect(SOUND_EFFECT_HEART_BEET_FAST, &effect, 11);
	LoadEffect(SOUND_EFFECT_GHOST_SHOWUP, &effect, 12);
	LoadEffect(SOUND_EFFECT_GHOST_CATCH, &effect, 13);
	LoadEffect(SOUND_EFFECT_MIMIC_SHOWUP, &effect, 14);
	LoadEffect(SOUND_EFFECT_SHADOW_SHOWUP, &effect, 15);
	LoadEffect(SOUND_EFFECT_SHADOW_SHOWUP_BEFORE, &effect, 16);
	LoadEffect(SOUND_EFFECT_SHADOW_CATCH, &effect, 17);
	LoadEffect(SOUND_EFFECT_STORY_TRIGGER, &effect, 18);
}

static void Start(GameObject* this)
{

}

static void Update(GameObject* this, int64 deltaTime)
{
	UpdateSound();
}


GameObject* SetSoundManager()
{
	LoadBGMSound();
	LoadEffectSound();

	_SoundManager = AllocGameObject();

	_SoundManager->layer = LAYER_COMMON_OBJECT;
	_SoundManager->posX = 0.0f;
	_SoundManager->posY = 0.0f;
	_SoundManager->rotation = 0.0f;
	_SoundManager->scaleX = 1.0f;
	_SoundManager->scaleY = 1.0f;
	_SoundManager->isLeftDir = true;
	_SoundManager->Start = Start;
	_SoundManager->Update = Update;
	_SoundManager->animArray = nullptr;

	return _SoundManager;
}


void PlayBGMSound(int num)
{
	PlayBGM(num);
}

void PlayEffectSound(int num)
{
	PlayEffect(num);
}

void StopSound(int num)
{
	SoundStop(num);
}

void PauseSound()
{
	PausedSound();
}
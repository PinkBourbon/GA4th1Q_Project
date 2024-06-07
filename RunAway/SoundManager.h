#pragma once

typedef struct _GameObject GameObject;

GameObject* SetSoundManager();
void PlayBGMSound(int num);
void PlayEffectSound(int num);
void StopSound(int num);
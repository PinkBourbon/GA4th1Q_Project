#pragma once

#define TEST1 "singing.wav"
#define TEST2 "swish.wav"


void CreateSoundSystem();

void LoadBGM(const char* filePath, void** bgmSound, int num);
void PlayBGM(int num);

void LoadEffect(const char* filePath, void** bgmSound, int num);
void LoadEffectOnce(const char* filePath, void** bgmSound, int num);
void PlayEffect(int num);


void PausedSound();
void SoundStop(int ChNumber);
void SoundAllStop();

void UpdateSound();

void DestroySound();

void SetBGMVolume(int ChNum);
void BGMVolumeUp();
void BGMVolumeDown();

void SetEffectVolume(int ChNum);
void EffectVolumeUp();
void EffectVolumeDown();
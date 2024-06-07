#pragma once
#include "RAType.h"

// 구조체 GameObject 전방선언
typedef struct _GameObject GameObject;


// 구조체 별명짓기
// 구조체 배열을 c파일안에 전역으로 가지고있고, 우리가 짠 모든 함수들을
// 전역에 있는 함수포인터를 사용하는 것에서, 이 구조체를 탐색해서 호출을
// 해주는 녀석들만 호출해준다.
typedef struct _KeyCallback 
{
	GameObject* gameObject;
	void(*_keyDownCallback)(GameObject* this, int32 InputKey);
	void(*_keyUpCallback)(GameObject* this, int32 InputKey);
}KeyCallback;

/// <summary>
/// input에서 사용하는 리스트를 초기화
/// </summary>
void InitializeInput();

// 해야할 것
// 이전 프레임에 눌렸는지를 체크하고, 얘가 첨이냐 아니냐
// 첨이면 down을 호출, 이전에 눌려져 있었는데 지금 아니면 up호출
void KeyBoardInputHandler();

void SetInputCallback(GameObject* obj,
	void(*keyUpCallBack)(GameObject* this, int32 vkKey),
	void(*keyDownCallBack)(GameObject* this, int32 vkKey));
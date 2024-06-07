#pragma once
#include "RAType.h"

// ����ü GameObject ���漱��
typedef struct _GameObject GameObject;


// ����ü ��������
// ����ü �迭�� c���Ͼȿ� �������� �������ְ�, �츮�� § ��� �Լ�����
// ������ �ִ� �Լ������͸� ����ϴ� �Ϳ���, �� ����ü�� Ž���ؼ� ȣ����
// ���ִ� �༮�鸸 ȣ�����ش�.
typedef struct _KeyCallback 
{
	GameObject* gameObject;
	void(*_keyDownCallback)(GameObject* this, int32 InputKey);
	void(*_keyUpCallback)(GameObject* this, int32 InputKey);
}KeyCallback;

/// <summary>
/// input���� ����ϴ� ����Ʈ�� �ʱ�ȭ
/// </summary>
void InitializeInput();

// �ؾ��� ��
// ���� �����ӿ� ���ȴ����� üũ�ϰ�, �갡 ÷�̳� �ƴϳ�
// ÷�̸� down�� ȣ��, ������ ������ �־��µ� ���� �ƴϸ� upȣ��
void KeyBoardInputHandler();

void SetInputCallback(GameObject* obj,
	void(*keyUpCallBack)(GameObject* this, int32 vkKey),
	void(*keyDownCallBack)(GameObject* this, int32 vkKey));
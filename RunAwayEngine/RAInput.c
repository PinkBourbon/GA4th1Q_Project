#include <Windows.h>
#include "RAInput.h"
#include "RAGameObject.h"
#include "RASingleList.h"
#include "RAType.h"
#include "RAMacro.h"


// gameobject�� NULL�̸�, �Ҵ���� ���� index��� �����Ѵ�.
// array�� ���鼭 �Ҵ�� �༮�� callback �� ȣ�����ָ� �ȴ�.
// �Ҵ��� �Ǿ���. = Ű���带 �Է��� ��ȭ�� ���� callback�Լ� ȣ��
//static keyCallback _keyCallbacks[100];
static RANode* _keyCallbackListHead;

static void CheckAndCallbackKey(int32 vkKey, bool* isDownKey)
{
	if (GetAsyncKeyState(vkKey) & 0x8001)
	{
		if (*isDownKey == false)
		{
			*isDownKey = true;
			RANode* currNode = _keyCallbackListHead->next;
			while (currNode != NULL)
			{
				KeyCallback* keyCallback = (KeyCallback*)(currNode->data);

				if (keyCallback->gameObject->state == GameObject_DISABLE)
				{
					currNode = currNode->next;
					continue;
				}

				keyCallback->_keyDownCallback(keyCallback->gameObject, vkKey);
				currNode = currNode->next;
			}
		}
	}
	else
	{
		if (*isDownKey == true)
		{
			*isDownKey = false;
			RANode* currNode = _keyCallbackListHead->next;
			while (currNode != NULL)
			{
				KeyCallback* keyCallback = (KeyCallback*)(currNode->data);

				if (keyCallback->gameObject->state == GameObject_DISABLE)
				{
					currNode = currNode->next;
					continue;
				}

				keyCallback->_keyUpCallback(keyCallback->gameObject, vkKey);
				currNode = currNode->next;
			}
		}
	}
}

void InitializeInput()
{
	_keyCallbackListHead = MakeNewList();
}

void KeyBoardInputHandler()
{
	// 8�� ���� ����(getasynckeystate�� ȣ���� ����)
	// �������ִ°�
	// 1�� �� �Լ��� ȣ��� ȣ���ϴ� ����, �� ������
	// �������� �ִ°�?

	// �Լ� ȣ���� �����ΰ�? ȣ������� ���������� Ȯ���غ�����
		// left�� ���� ���� Ű ���¸� ����ؾ��Ѵ�.
		// static ������ �ʿ�(�ٲ�� �ȵǴϱ�.)


	// assert �ڵ�� ����׿����� �۵��Ѵ�.
	//Assert(_keyDownCallback, "�Լ������� ������ �ȵ�.");
	//Assert(_keyUpCallback, "�Լ������� ������ �ȵ�.");
	static bool isDownLeft = false;
	CheckAndCallbackKey(VK_LEFT, &isDownLeft);

	static bool isDownDown = false;
	CheckAndCallbackKey(VK_DOWN, &isDownDown);

	static bool isDownRight = false;
	CheckAndCallbackKey(VK_RIGHT, &isDownRight);

	static bool isDownUP = false;
	CheckAndCallbackKey(VK_UP, &isDownUP);

	static bool isDownA = false;
	CheckAndCallbackKey(0x41, &isDownA);

	static bool isDownS = false;
	CheckAndCallbackKey(0x53, &isDownS);

	static bool isDownF = false;
	CheckAndCallbackKey(0x46, &isDownF);

	static bool isDownSpace = false;
	CheckAndCallbackKey(VK_SPACE, &isDownSpace);

	static bool isDownEnter = false;
	CheckAndCallbackKey(VK_RETURN, &isDownEnter);

	static bool isDownESC = false;
	CheckAndCallbackKey(VK_ESCAPE, &isDownESC);
}

// keydowncallback�̶�� �Լ������͸� �Ű������� �޴� �Լ� ����.
// ȣ�����ִ°� �ƴ϶�, �������ִ� �༮
// ���� �����ϸ� true �����ϸ� false
// keycallback�� �������ִ� �Լ�
// ����ִ°� ã�Ƽ� ����

void SetInputCallback(GameObject* obj, 
	void(*keyUpCallBack)(GameObject* this, int32 vkKey),
	void(*keyDownCallBack)(GameObject* this, int32 vkKey))
{
	KeyCallback* keyCallback = (KeyCallback*)malloc(sizeof(KeyCallback));
	if (keyCallback == NULL)
	{
		return;
	}

	keyCallback->gameObject = obj;
	keyCallback->_keyUpCallback = keyUpCallBack;
	keyCallback->_keyDownCallback = keyDownCallBack;

	AddNode(_keyCallbackListHead, keyCallback);
}
// ���ǻ���
// ���� �Լ������͸� 1���� ����� �� �ִ�.
// ���� ������Ʈ���� �ٸ� �Լ����� ������ ������ �ٲ���Ѵ�.
// �̺κ��� �����غ���....(�ٲٰ� �ɰ��̴�.)
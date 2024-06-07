#pragma once
#include "RAType.h"
#include "RARGB.h"

//typedef struct _RARgb RARgb;

/// <summary>
/// �޸𸮿� ��Ʈ�� ������ �ε��ϴ� �Լ�
/// </summary>
/// <param name="filePath">���� ���(�̸� ����)</param>
/// <param name="outWidth">��¿� ���� �ش� ��Ʈ���� �ʺ�</param>
/// <param name="outHeight">��¿� ���� �ش� ��Ʈ���� ����</param>
/// <returns>������ ������ ��� NULL�� ����</returns>
RARgb* LoadBitmap2(const char* filePath, int32* outWidth, int32* outHeight);

/// <summary>
/// �ε��� ��Ʈ�ʿ� ������ ��Ʈ���� �о� ������ �߰��ϴ� �Լ�
/// </summary>
/// <param name="filePath">���� ���(�̸� ����)</param>
/// <param name="bitmap">��¿� ���� �ε�� ��Ʈ�� �̹��� ������</param>
/// <param name="originX">��¿� ���� �ش� ��Ʈ���� ���� x��ǥ</param>
/// <param name="originY">��¿� ���� �ش� ��Ʈ���� ���� y ��ǥ</param>
/// <returns>���� ���Ͽ� ������ ������� NULL�� ����</returns>
RARgb* LoadInfoBitmap(const char* filePath, RARgb* bitmap, int32* originX, int32* originY);

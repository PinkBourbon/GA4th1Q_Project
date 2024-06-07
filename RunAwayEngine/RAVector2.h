#pragma once

typedef struct _Vector2
{
	float x;
	float y;
}Vector2;

/// <summary>
/// ���� ��
/// </summary>
/// <param name="vectorX"></param>
/// <param name="vectorY"></param>
/// <returns>���� ���� ��</returns>
Vector2 AddVector2(Vector2 vectorX, Vector2 vectorY);

/// <summary>
/// ���� ��
/// </summary>
/// <param name="vectorX"></param>
/// <param name="vectorY"></param>
/// <returns>�� ���� ��</returns>
Vector2 SubVector2(Vector2 vectorX, Vector2 vectorY);

/// <summary>
/// ������ ����
/// </summary>
/// <param name="vectorX"></param>
/// <param name="vectorY"></param>
/// <returns>������ ���� ��</returns>
float InnerProductVector2(Vector2 const vectorX, Vector2 const vectorY);

/// <summary>
/// ������ ũ�� ���ϱ�
/// </summary>
/// <param name="vector">ũ�⸦ ���� ����</param>
/// <returns>������ ũ��</returns>
float NormVector2(const Vector2* vector);

/// <summary>
/// ������ ũ�⸦ 1�� ����
/// </summary>
/// <param name="pVector">������ ����</param>
void NormalizationVector2(Vector2* pVector);


Vector2 AddVector2(Vector2 lhs, Vector2 rhs);
Vector2 SubVector2(Vector2 lhs, Vector2 rhs);


/// �ӽ� �Լ�
Vector2 AddVector2Point(const Vector2* const vectorX, const Vector2* const vectorY);
Vector2 SubVector2Point(const Vector2* const vectorX, const Vector2* const vectorY);
float InnerProductVector2Point(const Vector2* const vectorX, const Vector2* const vectorY);
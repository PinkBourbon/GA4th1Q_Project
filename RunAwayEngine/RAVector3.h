#pragma once

typedef struct _Vector3
{
	float x;
	float y;
	float z;
}Vector3;

void SetVector3(Vector3* pVector, float x, float y, float z);
/// <summary>
/// ����3�� ����
/// </summary>
/// <param name="lhs">���� ��</param>
/// <param name="rhs">������ ��</param>
/// <returns>������ ��</returns>
Vector3 AddVector3(Vector3 lhs, Vector3 rhs);

/// <summary>
/// ����3�� ����
/// </summary>
/// <param name="lhs">���� ��</param>
/// <param name="rhs">������ ��</param>
/// <returns>���� ��</returns>
Vector3 SubVector3(Vector3 lhs, Vector3 rhs);

/// <summary>
/// ����3�� �Ǽ��� ����
/// </summary>
/// <param name="lhs">���� ��</param>
/// <param name="rhs">��Į�� ��</param>
/// <returns>���� ��</returns>
Vector3 MulVector3(Vector3 lhs, float rhs);

/// <summary>
/// ����3�� ��������
/// </summary>
/// <param name="lhs">���� ��</param>
/// <param name="rhs">������ ��</param>
/// <returns>���� ��� ��</returns>
float DotVector3(Vector3 lhs, Vector3 rhs);


/// <summary>
/// ����3�� ��������
/// </summary>
/// <param name="lhs">���� ��</param>
/// <param name="rhs">������ ��</param>
/// <returns>���� ��� ��</returns>
Vector3 CrossVector3(Vector3 lhs, Vector3 rhs);

/// <summary>
/// ������ ũ�� ���ϱ�
/// </summary>
/// <param name="vector">ũ�⸦ ���� ����</param>
/// <returns>������ ũ��</returns>
float NormVector3(Vector3 vector);

/// <summary>
/// ������ ũ�⸦ 1�� ����
/// </summary>
/// <param name="pVector">������ ����</param>
void NormalizationVector3(Vector3* pVector);


/// <summary>
/// ����3�� ����
/// </summary>
/// <param name="lhs">���� ��</param>
/// <param name="rhs">������ ��</param>
/// <returns>������ ��</returns>
Vector3 AddVector3Point(const Vector3* const lhs, const Vector3* const rhs);


/// <summary>
/// ����3�� ����
/// </summary>
/// <param name="lhs">���� ��</param>
/// <param name="rhs">������ ��</param>
/// <returns>���� ��</returns>
Vector3 SubVector3Point(const Vector3* const lhs, const Vector3* const rhs);

/// <summary>
/// ����3�� �Ǽ��� ����
/// </summary>
/// <param name="lhs">���� ��</param>
/// <param name="rhs">��Į�� ��</param>
/// <returns>���� ��</returns>
Vector3 MulVector3Point(const Vector3* const lhs, const float* const rhs);

/// <summary>
/// ����3�� ��������
/// </summary>
/// <param name="lhs">���� ��</param>
/// <param name="rhs">������ ��</param>
/// <returns>���� ��� ��</returns>
float DotVector3Point(const Vector3* const lhs, const Vector3* const rhs);

/// <summary>
/// ����3�� �������� �ӵ��׽�Ʈ��
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
//float DotVector3Point2(const Vector3* const lhs, const Vector3* const rhs);

/// <summary>
/// ����3�� ��������
/// </summary>
/// <param name="lhs">���� ��</param>
/// <param name="rhs">������ ��</param>
/// <returns>���� ��� ��</returns>
Vector3 CrossVector3Point(Vector3* lhs, Vector3* rhs);


/// <summary>
/// ������ ũ�� ���ϱ�
/// </summary>
/// <param name="vector">ũ�⸦ ���� ����</param>
/// <returns>������ ũ��</returns>
float NormVector3Point(const Vector3* const vector);


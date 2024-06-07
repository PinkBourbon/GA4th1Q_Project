#pragma once
#include "RAVector3.h"

typedef struct _Matrix3
{
	float elements[9];
}Matrix3;

/// <summary>
/// ��� �� ����
/// </summary>
/// <param name="pMatrix">������ ���</param>
/// <param name="f0">1, 1</param>
/// <param name="f1">1, 2</param>
/// <param name="f2">1, 3</param>
/// <param name="f3">2, 1</param>
/// <param name="f4">2, 2</param>
/// <param name="f5">2, 3</param>
/// <param name="f6">3, 1</param>
/// <param name="f7">3, 2</param>
/// <param name="f8">3, 3</param>
void SetMatrix3(Matrix3* pMatrix, float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8);

/// <summary>
/// ��� ��
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>���� ��� ��</returns>
Matrix3 AddMatrix3(Matrix3 lhs, Matrix3 rhs);

/// <summary>
/// ��� ��
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs - rhs ��</returns>
Matrix3 SubMatrix3(Matrix3 lhs, Matrix3 rhs);

/// <summary>
/// ��Į�� * ���
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>��İ� ��Į�� ���� ��</returns>
Matrix3 ScalerMultMatrix3(float lhs, Matrix3 rhs);

/// <summary>
/// ���� * ���
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs * rhs�� ��</returns>
Vector3 Vector3MultMatrix3(Vector3 lhs, Matrix3 rhs);

/// <summary>
/// ��� * ���
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs * rhs�� ��</returns>
Matrix3 Matrix3MultMatrix3(Matrix3 lhs, Matrix3 rhs);

/// <summary>
/// ��Ľ�
/// </summary>
/// <param name="matrix"></param>
/// <returns>��Ľ��� ��</returns>
float DeterminantMatrix3(Matrix3 matrix);

/// <summary>
/// �����
/// </summary>
/// <param name="matrix"></param>
/// <returns>�����</returns>
Matrix3 InverseMatrix(Matrix3 matrix);



Matrix3 AddMatrix3Point(const Matrix3* const lhs, const Matrix3* const rhs);

/// <summary>
/// ��� ��
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs - rhs ��</returns>
Matrix3 SubMatrix3Point(const Matrix3* const lhs, const Matrix3* const rhs);

/// <summary>
/// ��Į�� * ���
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>��İ� ��Į�� ���� ��</returns>
Matrix3 ScalerMultMatrix3Point(const float* const lhs, const Matrix3* const rhs);

/// <summary>
/// ���� * ���
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs * rhs�� ��</returns>
Vector3 Vector3MultMatrix3Point(const Vector3* const lhs, const Matrix3* const rhs);

/// <summary>
/// ��� * ���
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs * rhs�� ��</returns>
Matrix3 Matrix3MultMatrix3Point(const Matrix3* const lhs, const Matrix3* const rhs);

/// <summary>
/// ��Ľ�
/// </summary>
/// <param name="matrix"></param>
/// <returns>��Ľ��� ��</returns>
float DeterminantMatrix3Point(const Matrix3* const matrix);

/// <summary>
/// �����
/// </summary>
/// <param name="matrix"></param>
/// <returns>�����</returns>
Matrix3 InverseMatrixPoint(const Matrix3* const matrix);
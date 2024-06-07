#pragma once

#include "RAVector2.h"

typedef struct _Matrix2
{
	float elements[4];

}Matrix2;


/// <summary>
/// ��� �� ����
/// </summary>
/// <param name="matrix">������ ���</param>
/// <param name="i">1, 1</param>
/// <param name="j">1, 2</param>
/// <param name="k">2, 1</param>
/// <param name="l">2, 2</param>
void InitMatrix2(Matrix2* matrix, float i, float j, float k, float l);

/// <summary>
/// ��� ��
/// </summary>
/// <param name="firstMatrix"></param>
/// <param name="secondMatrix"></param>
/// <returns>���� ��� ��</returns>
Matrix2 AddMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix);

/// <summary>
/// ��� ��
/// </summary>
/// <param name="firstMatrix"></param>
/// <param name="secondMatrix"></param>
/// <returns>�� ��� ��</returns>
Matrix2 SubMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix);

/// <summary>
/// ��� ��
/// </summary>
/// <param name="firstMatrix"></param>
/// <param name="secondMatrix"></param>
/// <returns>���� ��� ��</returns>
Matrix2 MulMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix);

/// <summary>
/// ���� * ���
/// </summary>
/// <param name="vector"></param>
/// <param name="matrix"></param>
/// <returns>���Ϳ� ����� ���� ��</returns>
Vector2 MulMatVec2(Vector2 vector, Matrix2 matrix);

/// �ӽ� �Լ�
Matrix2 AddMatrix2Point(const Matrix2* const firstMatrix, const Matrix2* const secondMatrix);
Matrix2 MulMatrix2Point(const Matrix2* const firstMatrix, const Matrix2* const secondMatrix);
Matrix2 SubMatrix2Point(const Matrix2* const firstMatrix, const Matrix2* const secondMatrix);
Vector2 MulMatVec2Point(const Vector2* const vector, const Matrix2* const matrix);
#pragma once
#include "RAVector3.h"

typedef struct _Matrix3
{
	float elements[9];
}Matrix3;

/// <summary>
/// 행렬 값 세팅
/// </summary>
/// <param name="pMatrix">세팅할 행렬</param>
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
/// 행렬 합
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>더한 행렬 값</returns>
Matrix3 AddMatrix3(Matrix3 lhs, Matrix3 rhs);

/// <summary>
/// 행렬 차
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs - rhs 값</returns>
Matrix3 SubMatrix3(Matrix3 lhs, Matrix3 rhs);

/// <summary>
/// 스칼라 * 행렬
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>행렬과 스칼라를 곱한 값</returns>
Matrix3 ScalerMultMatrix3(float lhs, Matrix3 rhs);

/// <summary>
/// 벡터 * 행렬
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs * rhs의 값</returns>
Vector3 Vector3MultMatrix3(Vector3 lhs, Matrix3 rhs);

/// <summary>
/// 행렬 * 행렬
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs * rhs의 값</returns>
Matrix3 Matrix3MultMatrix3(Matrix3 lhs, Matrix3 rhs);

/// <summary>
/// 행렬식
/// </summary>
/// <param name="matrix"></param>
/// <returns>행렬식의 값</returns>
float DeterminantMatrix3(Matrix3 matrix);

/// <summary>
/// 역행렬
/// </summary>
/// <param name="matrix"></param>
/// <returns>역행렬</returns>
Matrix3 InverseMatrix(Matrix3 matrix);



Matrix3 AddMatrix3Point(const Matrix3* const lhs, const Matrix3* const rhs);

/// <summary>
/// 행렬 차
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs - rhs 값</returns>
Matrix3 SubMatrix3Point(const Matrix3* const lhs, const Matrix3* const rhs);

/// <summary>
/// 스칼라 * 행렬
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>행렬과 스칼라를 곱한 값</returns>
Matrix3 ScalerMultMatrix3Point(const float* const lhs, const Matrix3* const rhs);

/// <summary>
/// 벡터 * 행렬
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs * rhs의 값</returns>
Vector3 Vector3MultMatrix3Point(const Vector3* const lhs, const Matrix3* const rhs);

/// <summary>
/// 행렬 * 행렬
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>lhs * rhs의 값</returns>
Matrix3 Matrix3MultMatrix3Point(const Matrix3* const lhs, const Matrix3* const rhs);

/// <summary>
/// 행렬식
/// </summary>
/// <param name="matrix"></param>
/// <returns>행렬식의 값</returns>
float DeterminantMatrix3Point(const Matrix3* const matrix);

/// <summary>
/// 역행렬
/// </summary>
/// <param name="matrix"></param>
/// <returns>역행렬</returns>
Matrix3 InverseMatrixPoint(const Matrix3* const matrix);
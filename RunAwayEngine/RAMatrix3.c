#include "RAMatrix3.h"



void SetMatrix3(Matrix3* pMatrix, 
	float f0, float f1, float f2, 
	float f3, float f4, float f5, 
	float f6, float f7, float f8)
{
	pMatrix->elements[0] = f0;
	pMatrix->elements[1] = f1;
	pMatrix->elements[2] = f2;
	pMatrix->elements[3] = f3;
	pMatrix->elements[4] = f4;
	pMatrix->elements[5] = f5;
	pMatrix->elements[6] = f6;
	pMatrix->elements[7] = f7;
	pMatrix->elements[8] = f8;
}

Matrix3 AddMatrix3(Matrix3 lhs, Matrix3 rhs)
{
	for (int i = 0; i < 9; ++i)
	{
		lhs.elements[i] += rhs.elements[i];
	}

	return lhs;
}

Matrix3 SubMatrix3(Matrix3 lhs, Matrix3 rhs)
{
	for (int i = 0; i < 9; ++i)
	{
		lhs.elements[i] -= rhs.elements[i];
	}

	return lhs;
}

Matrix3 ScalerMultMatrix3(float lhs, Matrix3 rhs)
{
	for (int i = 0; i < 9; ++i)
	{
		rhs.elements[i] *= lhs;
	}

	return rhs;
}

Vector3 Vector3MultMatrix3(Vector3 lhs, Matrix3 rhs)
{
	Vector3 vectorValue;
	vectorValue.x = lhs.x * rhs.elements[0] + lhs.y * rhs.elements[3] + lhs.z * rhs.elements[6];
	vectorValue.y = lhs.x * rhs.elements[1] + lhs.y * rhs.elements[4] + lhs.z * rhs.elements[7];
	vectorValue.z = lhs.x * rhs.elements[2] + lhs.y * rhs.elements[5] + lhs.z * rhs.elements[8];
	
	return vectorValue;
}


Matrix3 Matrix3MultMatrix3(Matrix3 lhs, Matrix3 rhs)
{
	Matrix3 multValue;
	multValue.elements[0] = (lhs.elements[0] * rhs.elements[0]) + (lhs.elements[1] * rhs.elements[3]) + (lhs.elements[2] * rhs.elements[6]);
	multValue.elements[1] = (lhs.elements[0] * rhs.elements[1]) + (lhs.elements[1] * rhs.elements[4]) + (lhs.elements[2] * rhs.elements[7]);
	multValue.elements[2] = (lhs.elements[0] * rhs.elements[2]) + (lhs.elements[1] * rhs.elements[5]) + (lhs.elements[2] * rhs.elements[8]);
	multValue.elements[3] = (lhs.elements[3] * rhs.elements[0]) + (lhs.elements[4] * rhs.elements[3]) + (lhs.elements[5] * rhs.elements[6]);
	multValue.elements[4] = (lhs.elements[3] * rhs.elements[1]) + (lhs.elements[4] * rhs.elements[4]) + (lhs.elements[5] * rhs.elements[7]);
	multValue.elements[5] = (lhs.elements[3] * rhs.elements[2]) + (lhs.elements[4] * rhs.elements[5]) + (lhs.elements[5] * rhs.elements[8]);
	multValue.elements[6] = (lhs.elements[6] * rhs.elements[0]) + (lhs.elements[7] * rhs.elements[3]) + (lhs.elements[8] * rhs.elements[6]);
	multValue.elements[7] = (lhs.elements[6] * rhs.elements[1]) + (lhs.elements[7] * rhs.elements[4]) + (lhs.elements[8] * rhs.elements[7]);
	multValue.elements[8] = (lhs.elements[6] * rhs.elements[2]) + (lhs.elements[7] * rhs.elements[5]) + (lhs.elements[8] * rhs.elements[8]);

	return multValue;
}

float DeterminantMatrix3(Matrix3 matrix)
{
	return (matrix.elements[0] * matrix.elements[4] * matrix.elements[8] + matrix.elements[1] * matrix.elements[5] * matrix.elements[6] + matrix.elements[2] * matrix.elements[3] * matrix.elements[7]
		- (matrix.elements[0] * matrix.elements[5] * matrix.elements[7] + matrix.elements[1] * matrix.elements[3] * matrix.elements[8] + matrix.elements[2] * matrix.elements[4] * matrix.elements[6]));
}



Matrix3 InverseMatrix(Matrix3 matrix)
{
	float determinant = DeterminantMatrix3(matrix);
	if ((determinant < 1.0E-38f && determinant >= 0) || 
		(determinant > -1.0E-38f && determinant <= 0))
	{
		return matrix;
	}

	Matrix3 inverse;
	inverse.elements[0] = matrix.elements[4] * matrix.elements[8] - matrix.elements[5] * matrix.elements[7];
	inverse.elements[1] = matrix.elements[2] * matrix.elements[7] - matrix.elements[1] * matrix.elements[8];
	inverse.elements[2] = matrix.elements[1] * matrix.elements[5] - matrix.elements[2] * matrix.elements[4];
	inverse.elements[3] = matrix.elements[5] * matrix.elements[6] - matrix.elements[3] * matrix.elements[8];
	inverse.elements[4] = matrix.elements[0] * matrix.elements[8] - matrix.elements[2] * matrix.elements[6];
	inverse.elements[5] = matrix.elements[2] * matrix.elements[3] - matrix.elements[0] * matrix.elements[5];
	inverse.elements[6] = matrix.elements[3] * matrix.elements[7] - matrix.elements[4] * matrix.elements[6];
	inverse.elements[7] = matrix.elements[1] * matrix.elements[6] - matrix.elements[0] * matrix.elements[7];
	inverse.elements[8] = matrix.elements[0] * matrix.elements[4] - matrix.elements[1] * matrix.elements[3];

	return ScalerMultMatrix3(1.0f / determinant, inverse);
}


Matrix3 AddMatrix3Point(const Matrix3* const lhs, const Matrix3* const rhs)
{
	Matrix3 tempMatrix;
	for (int i = 0; i < 9; ++i)
	{
		tempMatrix.elements[i] = lhs->elements[i] + rhs->elements[i];
	}

	return *lhs;
}

Matrix3 SubMatrix3Point(const Matrix3* const lhs, const Matrix3* const rhs)
{
	Matrix3 tempMatrix;
	for (int i = 0; i < 9; ++i)
	{
		tempMatrix.elements[i] = lhs->elements[i] - rhs->elements[i];
	}

	return *lhs;
}

Matrix3 ScalerMultMatrix3Point(const float* const lhs, const Matrix3* const rhs)
{
	Matrix3 tempMatrix;
	for (int i = 0; i < 9; ++i)
	{
		tempMatrix.elements[i] = rhs->elements[i] * (*lhs);
	}

	return tempMatrix;
}

Vector3 Vector3MultMatrix3Point(const Vector3* const lhs, const Matrix3* const rhs)
{
	Vector3 vectorValue;
	vectorValue.x = lhs->x * rhs->elements[0] + lhs->y * rhs->elements[3] + lhs->z * rhs->elements[6];
	vectorValue.y = lhs->x * rhs->elements[1] + lhs->y * rhs->elements[4] + lhs->z * rhs->elements[7];
	vectorValue.z = lhs->x * rhs->elements[2] + lhs->y * rhs->elements[5] + lhs->z * rhs->elements[8];

	return vectorValue;
}

Matrix3 Matrix3MultMatrix3Point(const Matrix3* const lhs, const Matrix3* const rhs)
{
	Matrix3 multValue;
	multValue.elements[0] = (lhs->elements[0] * rhs->elements[0]) + (lhs->elements[1] * rhs->elements[3]) + (lhs->elements[2] * rhs->elements[6]);
	multValue.elements[1] = (lhs->elements[0] * rhs->elements[1]) + (lhs->elements[1] * rhs->elements[4]) + (lhs->elements[2] * rhs->elements[7]);
	multValue.elements[2] = (lhs->elements[0] * rhs->elements[2]) + (lhs->elements[1] * rhs->elements[5]) + (lhs->elements[2] * rhs->elements[8]);
	multValue.elements[3] = (lhs->elements[3] * rhs->elements[0]) + (lhs->elements[4] * rhs->elements[3]) + (lhs->elements[5] * rhs->elements[6]);
	multValue.elements[4] = (lhs->elements[3] * rhs->elements[1]) + (lhs->elements[4] * rhs->elements[4]) + (lhs->elements[5] * rhs->elements[7]);
	multValue.elements[5] = (lhs->elements[3] * rhs->elements[2]) + (lhs->elements[4] * rhs->elements[5]) + (lhs->elements[5] * rhs->elements[8]);
	multValue.elements[6] = (lhs->elements[6] * rhs->elements[0]) + (lhs->elements[7] * rhs->elements[3]) + (lhs->elements[8] * rhs->elements[6]);
	multValue.elements[7] = (lhs->elements[6] * rhs->elements[1]) + (lhs->elements[7] * rhs->elements[4]) + (lhs->elements[8] * rhs->elements[7]);
	multValue.elements[8] = (lhs->elements[6] * rhs->elements[2]) + (lhs->elements[7] * rhs->elements[5]) + (lhs->elements[8] * rhs->elements[8]);

	return multValue;
}

float DeterminantMatrix3Point(const Matrix3* const matrix)
{
	return (matrix->elements[0] * matrix->elements[4] * matrix->elements[8] + matrix->elements[1] * matrix->elements[5] * matrix->elements[6] + matrix->elements[2] * matrix->elements[3] * matrix->elements[7]
		- (matrix->elements[0] * matrix->elements[5] * matrix->elements[7] + matrix->elements[1] * matrix->elements[3] * matrix->elements[8] + matrix->elements[2] * matrix->elements[4] * matrix->elements[6]));
}

Matrix3 InverseMatrixPoint(const Matrix3* const matrix)
{
	float determinant = DeterminantMatrix3(*matrix);
	if ((determinant < 1.0E-38f && determinant >= 0) ||
		(determinant > -1.0E-38f && determinant <= 0))
	{
		return *matrix;
	}

	Matrix3 inverse;
	inverse.elements[0] = matrix->elements[4] * matrix->elements[8] - matrix->elements[5] * matrix->elements[7];
	inverse.elements[1] = matrix->elements[2] * matrix->elements[7] - matrix->elements[1] * matrix->elements[8];
	inverse.elements[2] = matrix->elements[1] * matrix->elements[5] - matrix->elements[2] * matrix->elements[4];
	inverse.elements[3] = matrix->elements[5] * matrix->elements[6] - matrix->elements[3] * matrix->elements[8];
	inverse.elements[4] = matrix->elements[0] * matrix->elements[8] - matrix->elements[2] * matrix->elements[6];
	inverse.elements[5] = matrix->elements[2] * matrix->elements[3] - matrix->elements[0] * matrix->elements[5];
	inverse.elements[6] = matrix->elements[3] * matrix->elements[7] - matrix->elements[4] * matrix->elements[6];
	inverse.elements[7] = matrix->elements[1] * matrix->elements[6] - matrix->elements[0] * matrix->elements[7];
	inverse.elements[8] = matrix->elements[0] * matrix->elements[4] - matrix->elements[1] * matrix->elements[3];

	return ScalerMultMatrix3(1.0f / determinant, inverse);
}

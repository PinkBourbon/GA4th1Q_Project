#include "RAMatrix2.h"


void InitMatrix2(Matrix2* matrix, float i, float j, float k, float l)
{
	matrix->elements[0] = i;
	matrix->elements[1] = j;
	matrix->elements[2] = k;
	matrix->elements[3] = l;
}

Matrix2 AddMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix)
{
	firstMatrix.elements[0] += secondMatrix.elements[0];
	firstMatrix.elements[1] += secondMatrix.elements[1];
	firstMatrix.elements[2] += secondMatrix.elements[2];
	firstMatrix.elements[3] += secondMatrix.elements[3];

	return firstMatrix;
}

Matrix2 SubMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix)
{
	firstMatrix.elements[0] -= secondMatrix.elements[0];
	firstMatrix.elements[1] -= secondMatrix.elements[1];
	firstMatrix.elements[2] -= secondMatrix.elements[2];
	firstMatrix.elements[3] -= secondMatrix.elements[3];

	return firstMatrix;
}

Matrix2 MulMatrix2(Matrix2 firstMatrix, Matrix2 secondMatrix)
{
	Matrix2 result;

	result.elements[0] = firstMatrix.elements[0] * secondMatrix.elements[0] + firstMatrix.elements[1] * secondMatrix.elements[2];
	result.elements[1] = firstMatrix.elements[0] * secondMatrix.elements[1] + firstMatrix.elements[1] * secondMatrix.elements[3];
	result.elements[2] = firstMatrix.elements[2] * secondMatrix.elements[0] + firstMatrix.elements[3] * secondMatrix.elements[2];
	result.elements[3] = firstMatrix.elements[2] * secondMatrix.elements[1] + firstMatrix.elements[3] * secondMatrix.elements[3];

	return result;
}

Vector2 MulMatVec2(Vector2 vector, Matrix2 matrix)
{
	Vector2 result;

	result.x = vector.x * matrix.elements[0] + vector.y * matrix.elements[2];
	result.y = vector.x * matrix.elements[1] + vector.y * matrix.elements[3];

	return result;
}

Matrix2 AddMatrix2Point(const Matrix2* const firstMatrix, const Matrix2* const secondMatrix)
{
	Matrix2 tempMatrix2;
	tempMatrix2.elements[0] = firstMatrix->elements[0] + secondMatrix->elements[0];
	tempMatrix2.elements[1] = firstMatrix->elements[1] + secondMatrix->elements[1];
	tempMatrix2.elements[2] = firstMatrix->elements[2] + secondMatrix->elements[2];
	tempMatrix2.elements[3] = firstMatrix->elements[3] + secondMatrix->elements[3];

	return tempMatrix2;
}

Matrix2 SubMatrix2Point(const Matrix2* const firstMatrix, const Matrix2* const secondMatrix)
{
	Matrix2 tempMatrix2;
	tempMatrix2.elements[0] = firstMatrix->elements[0] - secondMatrix->elements[0];
	tempMatrix2.elements[1] = firstMatrix->elements[1] - secondMatrix->elements[1];
	tempMatrix2.elements[2] = firstMatrix->elements[2] - secondMatrix->elements[2];
	tempMatrix2.elements[3] = firstMatrix->elements[3] - secondMatrix->elements[3];

	return tempMatrix2;
}

Matrix2 MulMatrix2Point(const Matrix2* const firstMatrix, const Matrix2* const secondMatrix)
{
	Matrix2 result;

	result.elements[0] = firstMatrix->elements[0] * secondMatrix->elements[0] + firstMatrix->elements[1] * secondMatrix->elements[2];
	result.elements[1] = firstMatrix->elements[0] * secondMatrix->elements[1] + firstMatrix->elements[1] * secondMatrix->elements[3];
	result.elements[2] = firstMatrix->elements[2] * secondMatrix->elements[0] + firstMatrix->elements[3] * secondMatrix->elements[2];
	result.elements[3] = firstMatrix->elements[2] * secondMatrix->elements[1] + firstMatrix->elements[3] * secondMatrix->elements[3];

	return result;
}

Vector2 MulMatVec2Point(const Vector2* const vector, const Matrix2* const matrix)
{
	Vector2 result;

	result.x = vector->x * matrix->elements[0] + vector->y * matrix->elements[2];
	result.y = vector->x * matrix->elements[1] + vector->y * matrix->elements[3];

	return result;
}


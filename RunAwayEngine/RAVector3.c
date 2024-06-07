#include "RAVector3.h"
#include <math.h>

void SetVector3(Vector3* pVector, float x, float y, float z)
{
	pVector->x = x;
	pVector->y = y;
	pVector->z = z;
}

Vector3 AddVector3(Vector3 lhs, Vector3 rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;

	return lhs;
}
Vector3 SubVector3(Vector3 lhs, Vector3 rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;

	return lhs;
}
Vector3 MulVector3(Vector3 lhs, float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;

	return lhs;
}

float DotVector3(Vector3 lhs, Vector3 rhs)
{
	return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

Vector3 CrossVector3(Vector3 lhs, Vector3 rhs)
{
	Vector3 crossVector;
	crossVector.x = lhs.y * rhs.z - lhs.z * rhs.y;
	crossVector.y = lhs.z * rhs.x - lhs.x * rhs.z;
	crossVector.z = lhs.x * rhs.y - lhs.y * rhs.x;

	return crossVector;
}

float NormVector3(Vector3 vector)
{
	return sqrtf(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

void NormalizationVector3(Vector3* pVector)
{
	float norm = NormVector3(*pVector);

	if (norm < 1.0E-38)
	{
		return;
	}
	pVector->x *= 1 / norm;
	pVector->y *= 1 / norm;
	pVector->z *= 1 / norm;
	return;
}


Vector3 AddVector3Point(const Vector3* const lhs, const Vector3* const rhs)
{
	Vector3 tempVector;
	tempVector.x = lhs->x + rhs->x;
	tempVector.y = lhs->y + rhs->y;
	tempVector.z = lhs->z + rhs->z;

	return tempVector;
}
Vector3 SubVector3Point(const Vector3* const lhs, const Vector3* const rhs)
{
	Vector3 tempVector;
	tempVector.x = lhs->x - rhs->x;
	tempVector.y = lhs->y - rhs->y;
	tempVector.z = lhs->z - rhs->z;

	return tempVector;
}
Vector3 MulVector3Point(const Vector3* const lhs, const float* const rhs)
{
	Vector3 tempVector;
	tempVector.x = lhs->x * (*rhs);
	tempVector.y = lhs->y * (*rhs);
	tempVector.z = lhs->z * (*rhs);

	return tempVector;
}

float DotVector3Point(const Vector3* const lhs, const Vector3* const rhs)
{
	return (lhs->x * rhs->x) + (lhs->y * rhs->y) + (lhs->z * rhs->z);
}

// // 내적 속도테스트용으로 만들기
// float DotVector3Point2(const Vector3* const lhs, const Vector3* const rhs)
// {
// 	return (lhs->x * rhs->x) + (lhs->y * rhs->y) + (lhs->z * rhs->z);
// }

Vector3 CrossVector3Point(Vector3* lhs, Vector3* rhs)
{
	Vector3 crossVector;
	crossVector.x = lhs->y * rhs->z - lhs->z * rhs->y;
	crossVector.y = lhs->z * rhs->x - lhs->x * rhs->z;
	crossVector.z = lhs->x * rhs->y - lhs->y * rhs->x;

	return crossVector;
}

float NormVector3Point(const Vector3* const vector)
{
	return sqrtf(vector->x * vector->x + vector->y * vector->y + vector->z * vector->z);
}
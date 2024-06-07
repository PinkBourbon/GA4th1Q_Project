#include "pch.h"
#include "RAVector2.h"
#include <math.h>

Vector2 AddVector2(Vector2 vectorX, Vector2 vectorY)
{
	Vector2 vectorSum;
	vectorSum.x = vectorX.x + vectorY.x;
	vectorSum.y = vectorX.y + vectorY.y;

	return vectorSum;
}

Vector2 SubVector2(Vector2 vectorX, Vector2 vectorY)
{
	Vector2 vectorSub;
	vectorSub.x = vectorX.x - vectorY.x;
	vectorSub.y = vectorX.y - vectorY.y;

	return vectorSub;
}

float InnerProductVector2(Vector2 vectorX, Vector2 vectorY)
{

	float innerProduct = (vectorX.x * vectorY.x) + (vectorX.y * vectorY.y);

	return innerProduct;
}

float NormVector2(const Vector2* vector)
{
	return sqrtf(vector->x * vector->x + vector->y * vector->y);
}

void NormalizationVector2(Vector2* pVector)
{
	float norm = NormVector2(pVector);

	if (norm < 1.0E-38)
	{
		return;
	}
	pVector->x *= 1 / norm;
	pVector->y *= 1 / norm;
}

Vector2 AddVector2Point(const Vector2* const vectorX, const Vector2* const vectorY)
{
	Vector2 vectorSum;
	vectorSum.x = vectorX->x + vectorY->x;
	vectorSum.y = vectorX->y + vectorY->y;

	return vectorSum;
}

Vector2 SubVector2Point(const Vector2* const vectorX, const Vector2* const vectorY)
{
	Vector2 vectorSub;
	vectorSub.x = vectorX->x - vectorY->x;
	vectorSub.y = vectorX->y - vectorY->y;

	return vectorSub;
}

float InnerProductVector2Point(const Vector2* const vectorX, const Vector2* const vectorY)
{

	float innerProduct = (vectorX->x * vectorY->x) + (vectorX->y * vectorY->y);

	return innerProduct;
}

// 
// Vector2 AddVector2(Vector2 lhs, Vector2 rhs)
// {
// 	lhs.x += rhs.x;
// 	lhs.y += rhs.y;
// 	return lhs;
// }
// 
// Vector2 SubVector2(Vector2 lhs, Vector2 rhs)
// {
// 	lhs.x -= rhs.x;
// 	lhs.y -= rhs.y;
// 	return lhs;
// }
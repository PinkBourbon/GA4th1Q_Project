#pragma once

typedef struct _Vector2
{
	float x;
	float y;
}Vector2;

/// <summary>
/// 벡터 합
/// </summary>
/// <param name="vectorX"></param>
/// <param name="vectorY"></param>
/// <returns>더한 벡터 값</returns>
Vector2 AddVector2(Vector2 vectorX, Vector2 vectorY);

/// <summary>
/// 벡터 차
/// </summary>
/// <param name="vectorX"></param>
/// <param name="vectorY"></param>
/// <returns>뺀 벡터 값</returns>
Vector2 SubVector2(Vector2 vectorX, Vector2 vectorY);

/// <summary>
/// 벡터의 내적
/// </summary>
/// <param name="vectorX"></param>
/// <param name="vectorY"></param>
/// <returns>벡터의 내적 값</returns>
float InnerProductVector2(Vector2 const vectorX, Vector2 const vectorY);

/// <summary>
/// 벡터의 크기 구하기
/// </summary>
/// <param name="vector">크기를 구할 벡터</param>
/// <returns>벡터의 크기</returns>
float NormVector2(const Vector2* vector);

/// <summary>
/// 벡터의 크기를 1로 만듬
/// </summary>
/// <param name="pVector">변경할 벡터</param>
void NormalizationVector2(Vector2* pVector);


Vector2 AddVector2(Vector2 lhs, Vector2 rhs);
Vector2 SubVector2(Vector2 lhs, Vector2 rhs);


/// 임시 함수
Vector2 AddVector2Point(const Vector2* const vectorX, const Vector2* const vectorY);
Vector2 SubVector2Point(const Vector2* const vectorX, const Vector2* const vectorY);
float InnerProductVector2Point(const Vector2* const vectorX, const Vector2* const vectorY);
#pragma once

typedef struct _Vector3
{
	float x;
	float y;
	float z;
}Vector3;

void SetVector3(Vector3* pVector, float x, float y, float z);
/// <summary>
/// 벡터3의 덧셈
/// </summary>
/// <param name="lhs">왼쪽 값</param>
/// <param name="rhs">오른쪽 값</param>
/// <returns>합해진 값</returns>
Vector3 AddVector3(Vector3 lhs, Vector3 rhs);

/// <summary>
/// 벡터3의 뺄셈
/// </summary>
/// <param name="lhs">왼쪽 값</param>
/// <param name="rhs">오른쪽 값</param>
/// <returns>빼진 값</returns>
Vector3 SubVector3(Vector3 lhs, Vector3 rhs);

/// <summary>
/// 벡터3과 실수의 곱셈
/// </summary>
/// <param name="lhs">벡터 값</param>
/// <param name="rhs">스칼라 값</param>
/// <returns>곱한 값</returns>
Vector3 MulVector3(Vector3 lhs, float rhs);

/// <summary>
/// 벡터3의 내적연산
/// </summary>
/// <param name="lhs">왼쪽 값</param>
/// <param name="rhs">오른쪽 값</param>
/// <returns>내적 결과 값</returns>
float DotVector3(Vector3 lhs, Vector3 rhs);


/// <summary>
/// 벡터3의 외적연산
/// </summary>
/// <param name="lhs">왼쪽 값</param>
/// <param name="rhs">오른쪽 값</param>
/// <returns>외적 결과 값</returns>
Vector3 CrossVector3(Vector3 lhs, Vector3 rhs);

/// <summary>
/// 벡터의 크기 구하기
/// </summary>
/// <param name="vector">크기를 구할 벡터</param>
/// <returns>벡터의 크기</returns>
float NormVector3(Vector3 vector);

/// <summary>
/// 벡터의 크기를 1로 만듬
/// </summary>
/// <param name="pVector">변경할 벡터</param>
void NormalizationVector3(Vector3* pVector);


/// <summary>
/// 벡터3의 덧셈
/// </summary>
/// <param name="lhs">왼쪽 값</param>
/// <param name="rhs">오른쪽 값</param>
/// <returns>합해진 값</returns>
Vector3 AddVector3Point(const Vector3* const lhs, const Vector3* const rhs);


/// <summary>
/// 벡터3의 뺄셈
/// </summary>
/// <param name="lhs">왼쪽 값</param>
/// <param name="rhs">오른쪽 값</param>
/// <returns>빼진 값</returns>
Vector3 SubVector3Point(const Vector3* const lhs, const Vector3* const rhs);

/// <summary>
/// 벡터3과 실수의 곱셈
/// </summary>
/// <param name="lhs">벡터 값</param>
/// <param name="rhs">스칼라 값</param>
/// <returns>곱한 값</returns>
Vector3 MulVector3Point(const Vector3* const lhs, const float* const rhs);

/// <summary>
/// 벡터3의 내적연산
/// </summary>
/// <param name="lhs">왼쪽 값</param>
/// <param name="rhs">오른쪽 값</param>
/// <returns>내적 결과 값</returns>
float DotVector3Point(const Vector3* const lhs, const Vector3* const rhs);

/// <summary>
/// 벡터3의 내적연산 속도테스트용
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>
//float DotVector3Point2(const Vector3* const lhs, const Vector3* const rhs);

/// <summary>
/// 벡터3의 외적연산
/// </summary>
/// <param name="lhs">왼쪽 값</param>
/// <param name="rhs">오른쪽 값</param>
/// <returns>외적 결과 값</returns>
Vector3 CrossVector3Point(Vector3* lhs, Vector3* rhs);


/// <summary>
/// 벡터의 크기 구하기
/// </summary>
/// <param name="vector">크기를 구할 벡터</param>
/// <returns>벡터의 크기</returns>
float NormVector3Point(const Vector3* const vector);


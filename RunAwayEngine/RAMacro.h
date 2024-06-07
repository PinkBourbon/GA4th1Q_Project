#pragma once
#include <assert.h>

#ifdef __cplusplus

#else
///release������ ������� �ʽ��ϴ�.
#define Assert(cond, str) assert(cond && str)

#define static_assert(cond, str) char _temp[-!((void)str, (cond))]

#define Crash()\
do	\
{	\
	((void(*)())0)(); \
} while (false)

#endif
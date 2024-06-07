#pragma once

#ifdef __cplusplus

using BYTE = unsigned char;
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;

using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

#else

#undef bool
#define bool __int8
#undef true
#define true 1
#undef false
#define false 0

#undef nullptr
#define nullptr ((void*)0)

#undef int8
#define int8 __int8
#undef int16
#define int16 __int16
#undef int32
#define int32 __int32
#undef int64
#define int64 __int64

#undef uint8
#define uint8 unsigned __int8
#undef uint16
#define uint16 unsigned __int16
#undef uint32
#define uint32 unsigned __int32
#undef uint64
#define uint64 unsigned __int64

#endif

#define FALLTHROUGH
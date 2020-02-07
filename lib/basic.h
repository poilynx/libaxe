#ifndef BASIC_H_
#define BASIC_H_
#include "base.h"
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
typedef uint8_t ax_basic_type_t;
#define AX_BT_I8    0
#define AX_BT_I16   1
#define AX_BT_I32   2
#define AX_BT_I64   3
#define AX_BT_U8    4
#define AX_BT_U16   5
#define AX_BT_U32   6
#define AX_BT_U64   7
#define AX_BT_Z     8
#define AX_BT_F     9
#define AX_BT_LF    10
#define AX_BT_LLF   11
#define AX_BT_STR   12
#define AX_BT_PTR   13
#define AX_BT_RAW   14


union ax_basic_u
{
	int8_t   i8;
	int16_t  i16;
	int32_t  i32;
	int64_t  i64;
	uint8_t  u8;
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;
	size_t   z;
	float    f;
	double   lf;
	long double llf;
	char*    str;
	void*    ptr;
	void*    raw;
};
typedef union ax_basic_u ax_basic_t;


char*    ax_basic_name (ax_basic_type_t type);
size_t   ax_basic_size (ax_basic_type_t type);
void     ax_basic_vcopy(ax_basic_type_t type, ax_basic_t* basic, va_list arg);


#endif

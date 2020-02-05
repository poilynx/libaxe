#ifndef REF_H_
#define REF_H_
#include <stdarg.h>
#include "base.h"
struct ax_box_st;
typedef struct ax_box_st ax_box_t;

#define AX_RT_I8    0
#define AX_RT_I16   1
#define AX_RT_I32   2
#define AX_RT_I64   3
#define AX_RT_U8    4
#define AX_RT_U16   5
#define AX_RT_U32   6
#define AX_RT_U64   7
#define AX_RT_FLOAT 8
#define AX_RT_DOBLE 9
#define AX_RT_STR   10
#define AX_RT_PTR   11
#define AX_RT_BOX   12

union ax_clip_u
{
	int8_t   i8;
	int16_t  i16;
	int32_t  i32;
	int64_t  i64;
	uint8_t  u8;
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;
	float    f;
	double   lf;
	long double llf;
	char*    str;
	void*    ptr;
	ax_box_t*box;
};
typedef union ax_clip_u ax_clip_t;



struct ax_ref_st
{
	char type;
	void *ptr;
};
typedef struct ax_ref_st ax_ref_t;

size_t   ax_ref_size (unsigned char type);
void     ax_ref_vcopy(unsigned char type, ax_clip_t* clip, va_list arg);

int8_t   ax_ref_toi8 (ax_ref_t r);
int16_t  ax_ref_toi16(ax_ref_t r);
int32_t  ax_ref_toi32(ax_ref_t r);
int64_t  ax_ref_toi64(ax_ref_t r);
uint8_t  ax_ref_tou8 (ax_ref_t r);
uint16_t ax_ref_tou16(ax_ref_t r);
uint32_t ax_ref_tou32(ax_ref_t r);
uint64_t ax_ref_tou64(ax_ref_t r);
float    ax_ref_tof  (ax_ref_t r);
double   ax_ref_tolf (ax_ref_t r);
char*    ax_ref_tostr(ax_ref_t r)
void*    ax_ref_toptr(ax_ref_t r)
ax_box_t*ax_ref_tobox(ax_ref_t r)

#endif

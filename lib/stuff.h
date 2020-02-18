#ifndef STUFF_H_
#define STUFF_H_
#include "def.h"
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
typedef uint8_t ax_stuff_type_t;
#define AX_ST_NIL   0
#define AX_ST_RAW   1
#define AX_ST_I8    2
#define AX_ST_I16   3
#define AX_ST_I32   4
#define AX_ST_I64   5
#define AX_ST_U8    6
#define AX_ST_U16   7
#define AX_ST_U32   8
#define AX_ST_U64   9
#define AX_ST_Z     10
#define AX_ST_F     11
#define AX_ST_LF    12
#define AX_ST_LLF   13
#define AX_ST_STR   14
#define AX_ST_PTR   15
#define AX_ST_PWL   16


union ax_stuff_u
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
typedef union ax_stuff_u ax_stuff_t;

typedef void      (*ax_stuff_free_f) (const void* e);
typedef size_t    (*ax_stuff_hash_f) (const void* e);
typedef ax_bool_t (*ax_stuff_comp_f) (const void* e1, const void* e2);
typedef void      (*ax_stuff_copy_f) (void* e1, const void* e2);
typedef char*     (*ax_stuff_text_f)(const void* e);

struct ax_stuff_trait_st
{
	const char       type;
	const size_t     size;
	ax_stuff_comp_f  equal;
	ax_stuff_comp_f  less;
	ax_stuff_hash_f  hash;
	ax_stuff_free_f  free; 
	ax_stuff_copy_f  copy;
	ax_stuff_copy_f  move;
	ax_stuff_text_f  text;
};
typedef struct ax_stuff_trait_st ax_stuff_trait_t;

char*  ax_stuff_name (ax_stuff_type_t type);
size_t ax_stuff_size (ax_stuff_type_t type);
void   ax_stuff_set(char type, ax_stuff_t* stuff, va_list arg);
const ax_stuff_trait_t* ax_stuff_get_trait(char type);

#endif

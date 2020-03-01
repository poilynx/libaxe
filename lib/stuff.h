/*
 * Copyright (c) 2020 Li hsilin <lihsilyn@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef STUFF_H_
#define STUFF_H_
#include "def.h"
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
typedef uint8_t ax_stuff_type;
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
typedef union ax_stuff_u ax_stuff;

typedef void      (*ax_stuff_free_f) (const void* e);
typedef size_t    (*ax_stuff_hash_f) (const void* e);
typedef bool      (*ax_stuff_comp_f) (const void* e1, const void* e2);
typedef void      (*ax_stuff_copy_f) (void* e1, const void* e2);
typedef char*     (*ax_stuff_text_f) (const void* e);

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
typedef struct ax_stuff_trait_st ax_stuff_trait;

ax_stuff_type ax_stuff_pwl  (char c);
char*         ax_stuff_name (ax_stuff_type type);
size_t        ax_stuff_size (ax_stuff_type type);
void          ax_stuff_set  (char type, ax_stuff* stuff, va_list arg);
const         ax_stuff_trait* ax_stuff_traits(ax_stuff_type type);

#endif

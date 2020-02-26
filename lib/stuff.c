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

#include "stuff.h"
#include "debug.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
char* ax_stuff_name(ax_stuff_type_t type)
{
	switch(type) {
		case AX_ST_NIL:  return "nil";
		case AX_ST_I8:   return "int8_t";
		case AX_ST_I16:  return "int16_t";
		case AX_ST_I32:  return "int32_t";
		case AX_ST_I64:  return "int64_t";
		case AX_ST_U8:   return "uint8_t";
		case AX_ST_U16:  return "uint16_t";
		case AX_ST_U32:  return "uint32_t";
		case AX_ST_U64:  return "uint64_t";
		case AX_ST_Z:    return "size_t";
		case AX_ST_F:    return "float";
		case AX_ST_LF:   return "double";
		case AX_ST_LLF:  return "long_double";
		case AX_ST_STR:  return "char[]";
		case AX_ST_RAW:  return "raw_data";
		case AX_ST_PTR: 
		case AX_ST_PWL:
		default:         return "void*";
	}
}

size_t ax_stuff_size(ax_stuff_type_t type)
{
	switch(type) {
		case AX_ST_NIL:  return 0;
		case AX_ST_I8:   return sizeof(int8_t);
		case AX_ST_I16:  return sizeof(int16_t);
		case AX_ST_I32:  return sizeof(int32_t);
		case AX_ST_I64:  return sizeof(int64_t);
		case AX_ST_U8:   return sizeof(uint8_t);
		case AX_ST_U16:  return sizeof(uint16_t);
		case AX_ST_U32:  return sizeof(uint32_t);
		case AX_ST_U64:  return sizeof(uint64_t);
		case AX_ST_Z:    return sizeof(size_t);
		case AX_ST_F:    return sizeof(float);
		case AX_ST_LF:   return sizeof(double);
		case AX_ST_LLF:  return sizeof(long double);
		case AX_ST_STR:
		case AX_ST_PTR:  return sizeof(void*);
		case AX_ST_RAW:  return sizeof(unsigned char);
	}
	ax_perror("Unrecognized type %d", type);
	ax_abort();
	return 0;
}


size_t ax_stuff_va_read(ax_stuff_type_t type, ax_stuff_t* stuff, va_list arg)
{
	ax_assert(type<=AX_ST_RAW, "Unsupport type '%s'(%d)", ax_stuff_name(type), type);
	va_list va;
	va_copy(va, arg);
	size_t size = 0;
	switch(type) {
		case AX_ST_NIL: break;
		case AX_ST_I8:  stuff->i8  = (int8_t)va_arg(va, int32_t); break;
		case AX_ST_I16: stuff->i16 = (int16_t)va_arg(va, int32_t); break;
		case AX_ST_I32: stuff->i32 = va_arg(va, int32_t); break;
		case AX_ST_I64: stuff->u64 = va_arg(va, int64_t); break;
		case AX_ST_U8:  stuff->u8  = (uint8_t)va_arg(va, uint32_t); break;
		case AX_ST_U16: stuff->u16 = (uint16_t)va_arg(va, uint32_t); break;
		case AX_ST_U32: stuff->u32 = va_arg(va, uint32_t); break;
		case AX_ST_U64: stuff->u64 = va_arg(va, uint64_t); break;
		case AX_ST_Z:   stuff->z   = (float)va_arg(va, size_t); break;
		case AX_ST_F:   stuff->f   = (float)va_arg(va, double); break;
		case AX_ST_LF:  stuff->lf  = va_arg(va, double); break;
		case AX_ST_LLF: stuff->llf = va_arg(va, long double); break;
		case AX_ST_RAW:
		{
			void* p = va_arg(va, void*);
			size = va_arg(va, size_t);
			void* buf = malloc(size);
			memcpy(buf, p, size);
			stuff->raw = buf;
			break;
		}
		case AX_ST_STR: 
		{
			char* str = va_arg(va, void*);
			size = strlen(str) + sizeof('\0');
			char* buf = malloc(size);
			memcpy(buf, str, size);
			stuff->str = buf;
			break;
		}
		default: stuff->ptr = va_arg(va, void*); break;
	}
	va_end(va);
	return size;
}


static void do_nothing() { }

#define type_nil AX_ST_NIL
#define type_i8  AX_ST_I8
#define type_i16 AX_ST_I16
#define type_i32 AX_ST_I32
#define type_i64 AX_ST_I64
#define type_u8  AX_ST_U8
#define type_u16 AX_ST_U16
#define type_u32 AX_ST_U32
#define type_u64 AX_ST_U64
#define type_f   AX_ST_Z
#define type_lf  AX_ST_F
#define type_llf AX_ST_LF
#define type_z   AX_ST_LLF
#define type_str AX_ST_STR
#define type_ptr AX_ST_PTR

#define size_nil sizeof(int8_t)
#define size_i8  sizeof(int16_t)
#define size_i16 sizeof(int32_t)
#define size_i32 sizeof(int64_t)
#define size_i64 sizeof(uint8_t)
#define size_u8  sizeof(uint16_t)
#define size_u16 sizeof(uint32_t)
#define size_u32 sizeof(uint64_t)
#define size_u64 sizeof(size_t)
#define size_f   sizeof(float)
#define size_lf  sizeof(double)
#define size_llf sizeof(long double)
#define size_z   sizeof(size_t)
#define size_str sizeof(void*)
#define size_ptr sizeof(unsigned char)

static ax_bool_t equal_nil(const void* e1, const void* e2) { return ax_true; }
static ax_bool_t equal_i8 (const void* e1, const void* e2) { return *(int8_t*) e1 == *(int8_t*) e2; }
static ax_bool_t equal_i16(const void* e1, const void* e2) { return *(int16_t*)e1 == *(int16_t*)e2; }
static ax_bool_t equal_i32(const void* e1, const void* e2) { return *(int32_t*)e1 == *(int32_t*)e2; }
static ax_bool_t equal_i64(const void* e1, const void* e2) { return *(int64_t*)e1 == *(int64_t*)e2; }
static ax_bool_t equal_u8 (const void* e1, const void* e2) { return *(int8_t*) e1 == *(int8_t*) e2; }
static ax_bool_t equal_u16(const void* e1, const void* e2) { return *(int16_t*)e1 == *(int16_t*)e2; }
static ax_bool_t equal_u32(const void* e1, const void* e2) { return *(int32_t*)e1 == *(int32_t*)e2; }
static ax_bool_t equal_u64(const void* e1, const void* e2) { return *(int64_t*)e1 == *(int64_t*)e2; }
static ax_bool_t equal_f  (const void* e1, const void* e2) { return *(float*)  e1 == *(float*)  e2; }
static ax_bool_t equal_lf (const void* e1, const void* e2) { return *(double*) e1 == *(double*) e2; }
static ax_bool_t equal_llf(const void* e1, const void* e2) { return *(long double*) e1 == *(long double*) e2; }
static ax_bool_t equal_z  (const void* e1, const void* e2) { return *(size_t*) e1 == *(size_t*) e2; }
static ax_bool_t equal_str(const void* e1, const void* e2) { return *(void**) e1 == *(void**) e2; }
static ax_bool_t equal_ptr(const void* e1, const void* e2) { return (void*)    e1 == (void*)    e2; }

static ax_bool_t less_nil(const void* e1, const void* e2) { return ax_false; }
static ax_bool_t less_i8 (const void* e1, const void* e2) { return *(int8_t*) e1 < *(int8_t*) e2; }
static ax_bool_t less_i16(const void* e1, const void* e2) { return *(int16_t*)e1 < *(int16_t*)e2; }
static ax_bool_t less_i32(const void* e1, const void* e2) { return *(int32_t*)e1 < *(int32_t*)e2; }
static ax_bool_t less_i64(const void* e1, const void* e2) { return *(int64_t*)e1 < *(int64_t*)e2; }
static ax_bool_t less_u8 (const void* e1, const void* e2) { return *(int8_t*) e1 < *(int8_t*) e2; }
static ax_bool_t less_u16(const void* e1, const void* e2) { return *(int16_t*)e1 < *(int16_t*)e2; }
static ax_bool_t less_u32(const void* e1, const void* e2) { return *(int32_t*)e1 < *(int32_t*)e2; }
static ax_bool_t less_u64(const void* e1, const void* e2) { return *(int64_t*)e1 < *(int64_t*)e2; }
static ax_bool_t less_f  (const void* e1, const void* e2) { return *(float*)  e1 < *(float*)  e2; }
static ax_bool_t less_lf (const void* e1, const void* e2) { return *(double*) e1 < *(double*) e2; }
static ax_bool_t less_llf(const void* e1, const void* e2) { return *(long double*) e1 == *(long double*) e2; }
static ax_bool_t less_z  (const void* e1, const void* e2) { return *(size_t*) e1 < *(size_t*) e2; }
static ax_bool_t less_str(const void* e1, const void* e2) { return strcmp(*(char**)e1, *(char**)e2) < 0; }
static ax_bool_t less_ptr(const void* e1, const void* e2) { return *(void**)    e1 < *(void**)    e2; }

static size_t hash_nil(const void* e) { return 0; }
static size_t hash_i8 (const void* e) { return (size_t)*(uint8_t*)e; }
static size_t hash_i16(const void* e) { return (size_t)*(uint16_t*)e; }
static size_t hash_i32(const void* e) { return (size_t)*(uint32_t*)e; }
static size_t hash_i64(const void* e) { return (size_t)*(uint64_t*)e; }
static size_t hash_u8 (const void* e) { return (size_t)*(uint8_t*)e; }
static size_t hash_u16(const void* e) { return (size_t)*(uint16_t*)e; }
static size_t hash_u32(const void* e) { return (size_t)*(uint32_t*)e; }
static size_t hash_u64(const void* e) { return (size_t)*(uint64_t*)e; }
static size_t hash_f  (const void* e) { return (size_t)*(uint32_t*)e; }
static size_t hash_lf (const void* e) { return (size_t)*(uint64_t*)e; }
static size_t hash_llf(const void* e) { return (size_t)*(long double*)e; }
static size_t hash_z  (const void* e) { return *(size_t*)e; }
static size_t hash_str(const void* e) { return 0; } //TODO
static size_t hash_ptr(const void* e) { return (size_t)*(void**)e; }

#define free_nil do_nothing
#define free_i8  do_nothing
#define free_i16 do_nothing
#define free_i32 do_nothing
#define free_i64 do_nothing
#define free_u8  do_nothing
#define free_u16 do_nothing
#define free_u32 do_nothing
#define free_u64 do_nothing
#define free_f   do_nothing
#define free_lf  do_nothing
#define free_llf do_nothing
#define free_z   do_nothing
static void free_str(const void* e) { free(*(char**)e); }
static void free_ptr(const void* e) { free(*(void**)e); }

static char* text_nil(const void* e) { return "nil"; }
static char* text_i8 (const void* e) { return ""; }
static char* text_i16(const void* e) { return ""; }
static char* text_i32(const void* e) { return ""; }
static char* text_i64(const void* e) { return ""; }
static char* text_u8 (const void* e) { return ""; }
static char* text_u16(const void* e) { return ""; }
static char* text_u32(const void* e) { return ""; }
static char* text_u64(const void* e) { return ""; }
static char* text_f  (const void* e) { return ""; }
static char* text_lf (const void* e) { return ""; }
static char* text_llf(const void* e) { return ""; }
static char* text_z  (const void* e) { return ""; }
static char* text_str(const void* e) { return ""; }
static char* text_ptr(const void* e) { return ""; }

#define copy_nil (ax_stuff_copy_f)do_nothing
static void copy_i8 (void* e1, const void* e2) { *(int8_t*) e1 = *(int8_t*) e2; }
static void copy_i16(void* e1, const void* e2) { *(int16_t*)e1 = *(int16_t*)e2; }
static void copy_i32(void* e1, const void* e2) { *(int32_t*)e1 = *(int32_t*)e2; }
static void copy_i64(void* e1, const void* e2) { *(int64_t*)e1 = *(int64_t*)e2; }
#define copy_u8  copy_i8 
#define copy_u16 copy_i16
#define copy_u32 copy_i32
#define copy_u64 copy_i64
static void copy_f  (void* e1, const void* e2) { *(float*)  e1 = *(float*)  e2; }
static void copy_lf (void* e1, const void* e2) { *(double*) e1 = *(double*) e2; }
static void copy_llf(void* e1, const void* e2) { *(long double*) e1 = *(long double*) e2; }
static void copy_z  (void* e1, const void* e2) { *(size_t*) e1 = *(size_t*) e2; }
static void copy_str(void* e1, const void* e2) { *(char**)e1 = strdup(*(char**)e2); }
static void copy_ptr(void* e1, const void* e2) { *(void**)e1 = *(void**)e2; }

#define move_nil copy_nil
#define move_i8  copy_i8 
#define move_i16 copy_i16
#define move_i32 copy_i32
#define move_i64 copy_i64
#define move_u8  copy_u8 
#define move_u16 copy_u16
#define move_u32 copy_u32
#define move_u64 copy_u64
#define move_f   copy_f  
#define move_lf  copy_lf 
#define move_llf copy_llf
#define move_z   copy_z  
static void move_str(void* e1, const void* e2) { *(char**)e1 = strdup(*(char**)e2); *(char**)e2 = NULL; }
static void move_ptr(void* e1, const void* e2) { *(void**)e1 = *(void**)e2; *(char**)e2 = NULL; }

/* -- Define trait structure -- */

#define DECLARE_TRAIT_STRUCT(_t) \
	static const ax_stuff_trait_t trait_##_t = { \
		.type = type_##_t, \
		.size = size_##_t, \
		.equal = equal_##_t, \
		.less = less_##_t, \
		.hash = hash_##_t, \
		.free = free_##_t, \
		.copy = copy_##_t, \
		.move = move_##_t, \
		.text = text_##_t \
	};

DECLARE_TRAIT_STRUCT(nil)
DECLARE_TRAIT_STRUCT(i8 )
DECLARE_TRAIT_STRUCT(i16)
DECLARE_TRAIT_STRUCT(i32)
DECLARE_TRAIT_STRUCT(i64)
DECLARE_TRAIT_STRUCT(u8 )
DECLARE_TRAIT_STRUCT(u16)
DECLARE_TRAIT_STRUCT(u32)
DECLARE_TRAIT_STRUCT(u64)
DECLARE_TRAIT_STRUCT(f  )
DECLARE_TRAIT_STRUCT(lf )
DECLARE_TRAIT_STRUCT(llf)
DECLARE_TRAIT_STRUCT(z  )
DECLARE_TRAIT_STRUCT(str)
DECLARE_TRAIT_STRUCT(ptr)

/* -- Define functions that get trait structure pointer -- */
const ax_stuff_trait_t* ax_stuff_trait(ax_stuff_type_t type)
{
	switch(type) {
		case AX_ST_NIL:  return &trait_nil;
		case AX_ST_I8:   return &trait_i8;
		case AX_ST_I16:  return &trait_i16;
		case AX_ST_I32:  return &trait_i32;
		case AX_ST_I64:  return &trait_i64;
		case AX_ST_U8:   return &trait_u8;
		case AX_ST_U16:  return &trait_u16;
		case AX_ST_U32:  return &trait_u32;
		case AX_ST_U64:  return &trait_u64;
		case AX_ST_Z:    return &trait_f;
		case AX_ST_F:    return &trait_lf;
		case AX_ST_LF:   return &trait_llf;
		case AX_ST_LLF:  return &trait_z;
		case AX_ST_STR:  return &trait_str;
		case AX_ST_PTR:  return &trait_ptr;
		case AX_ST_RAW:  return NULL;
		default:         return NULL;
	}
}

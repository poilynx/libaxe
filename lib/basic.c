#include "basic.h"
#include "debug.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
char* ax_basic_name(ax_basic_type_t type)
{
	switch(type) {
		case AX_BT_I8:   return "int8_t";
		case AX_BT_I16:  return "int16_t";
		case AX_BT_I32:  return "int32_t";
		case AX_BT_I64:  return "int64_t";
		case AX_BT_U8:   return "uint8_t";
		case AX_BT_U16:  return "uint16_t";
		case AX_BT_U32:  return "uint32_t";
		case AX_BT_U64:  return "uint64_t";
		case AX_BT_Z:    return "size_t";
		case AX_BT_F:    return "float";
		case AX_BT_LF:   return "double";
		case AX_BT_LLF:  return "long_double";
		case AX_BT_STR:  return "char[]";
		case AX_BT_PTR:  return "void*";
		case AX_BT_RAW:  return "raw_data";
		default:         return "unknow_type";
	}
}

size_t ax_basic_size(ax_basic_type_t type)
{
	switch(type) {
		case AX_BT_I8:   return sizeof(int8_t);
		case AX_BT_I16:  return sizeof(int16_t);
		case AX_BT_I32:  return sizeof(int32_t);
		case AX_BT_I64:  return sizeof(int64_t);
		case AX_BT_U8:   return sizeof(uint8_t);
		case AX_BT_U16:  return sizeof(uint16_t);
		case AX_BT_U32:  return sizeof(uint32_t);
		case AX_BT_U64:  return sizeof(uint64_t);
		case AX_BT_Z:    return sizeof(size_t);
		case AX_BT_F:    return sizeof(float);
		case AX_BT_LF:   return sizeof(double);
		case AX_BT_LLF:  return sizeof(long double);
		case AX_BT_STR:
		case AX_BT_PTR:  return sizeof(void*);
		case AX_BT_RAW:  return sizeof(unsigned char);
	}
	ax_fault("Unrecognized type %d", type);
	return 0;
}


size_t ax_basic_va_read(ax_basic_type_t type, ax_basic_t* basic, va_list arg)
{
	ax_assert(type<=AX_BT_RAW, "Unsupport type '%s'(%d)", ax_basic_name(type), type);
	va_list va;
	va_copy(va, arg);
	size_t size = 0;
	switch(type) {
		case AX_BT_I8:  basic->i8  = (int8_t)va_arg(va, int32_t); break;
		case AX_BT_I16: basic->i16 = (int16_t)va_arg(va, int32_t); break;
		case AX_BT_I32: basic->i32 = va_arg(va, int32_t); break;
		case AX_BT_I64: basic->u64 = va_arg(va, int64_t); break;
		case AX_BT_U8:  basic->u8  = (uint8_t)va_arg(va, uint32_t); break;
		case AX_BT_U16: basic->u16 = (uint16_t)va_arg(va, uint32_t); break;
		case AX_BT_U32: basic->u32 = va_arg(va, uint32_t); break;
		case AX_BT_U64: basic->u64 = va_arg(va, uint64_t); break;
		case AX_BT_Z:   basic->z   = (float)va_arg(va, size_t); break;
		case AX_BT_F:   basic->f   = (float)va_arg(va, double); break;
		case AX_BT_LF:  basic->lf  = va_arg(va, double); break;
		case AX_BT_LLF: basic->llf = va_arg(va, long double); break;
		case AX_BT_PTR: basic->ptr = va_arg(va, void*); break;
		case AX_BT_STR: 
		{
			char* str = va_arg(va, void*);
			size = strlen(str) + sizeof('\0');
			char* buf = malloc(size);
			memcpy(buf, str, size);
			basic->str = buf;
			break;
		}
		case AX_BT_RAW:
		{
			void* p = va_arg(va, void*);
			size = va_arg(va, size_t);
			void* buf = malloc(size);
			memcpy(buf, p, size);
			basic->raw = buf;
			break;
		}
		break;
	}
	va_end(va);
	return size;
}

static ax_basic_type_t type_i8 (const void* e) { return AX_BT_I8; }
static ax_basic_type_t type_i16(const void* e) { return AX_BT_I16; }
static ax_basic_type_t type_i32(const void* e) { return AX_BT_I32; }
static ax_basic_type_t type_i64(const void* e) { return AX_BT_I64; }
static ax_basic_type_t type_u8 (const void* e) { return AX_BT_U8; } 
static ax_basic_type_t type_u16(const void* e) { return AX_BT_U16; }
static ax_basic_type_t type_u32(const void* e) { return AX_BT_U32; }
static ax_basic_type_t type_u64(const void* e) { return AX_BT_U64; }
static ax_basic_type_t type_f  (const void* e) { return AX_BT_Z; }  
static ax_basic_type_t type_lf (const void* e) { return AX_BT_F; }  
static ax_basic_type_t type_llf(const void* e) { return AX_BT_LF; } 
static ax_basic_type_t type_z  (const void* e) { return AX_BT_LLF; }
static ax_basic_type_t type_str(const void* e) { return AX_BT_STR; }
static ax_basic_type_t type_ptr(const void* e) { return AX_BT_PTR; }

static size_t size_i8 (const void* e) { return ax_basic_size(AX_BT_I8); }
static size_t size_i16(const void* e) { return ax_basic_size(AX_BT_I16); }
static size_t size_i32(const void* e) { return ax_basic_size(AX_BT_I32); }
static size_t size_i64(const void* e) { return ax_basic_size(AX_BT_I64); }
static size_t size_u8 (const void* e) { return ax_basic_size(AX_BT_U8); } 
static size_t size_u16(const void* e) { return ax_basic_size(AX_BT_U16); }
static size_t size_u32(const void* e) { return ax_basic_size(AX_BT_U32); }
static size_t size_u64(const void* e) { return ax_basic_size(AX_BT_U64); }
static size_t size_f  (const void* e) { return ax_basic_size(AX_BT_Z); }  
static size_t size_lf (const void* e) { return ax_basic_size(AX_BT_F); }  
static size_t size_llf(const void* e) { return ax_basic_size(AX_BT_LF); } 
static size_t size_z  (const void* e) { return ax_basic_size(AX_BT_LLF); }
static size_t size_str(const void* e) { return ax_basic_size(AX_BT_STR); }
static size_t size_ptr(const void* e) { return ax_basic_size(AX_BT_PTR); }




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


static void free_none(const void* e) { }
#define free_i8  free_none
#define free_i16 free_none
#define free_i32 free_none
#define free_i64 free_none
#define free_u8  free_none
#define free_u16 free_none
#define free_u32 free_none
#define free_u64 free_none
#define free_f   free_none
#define free_lf  free_none
#define free_llf free_none
#define free_z   free_none
static void free_str(const void* e) { free(*(char**)e); }
static void free_ptr(const void* e) { free(*(void**)e); }

static char* tostr_i8 (const void* e) { return ""; }
static char* tostr_i16(const void* e) { return ""; }
static char* tostr_i32(const void* e) { return ""; }
static char* tostr_i64(const void* e) { return ""; }
static char* tostr_u8 (const void* e) { return ""; }
static char* tostr_u16(const void* e) { return ""; }
static char* tostr_u32(const void* e) { return ""; }
static char* tostr_u64(const void* e) { return ""; }
static char* tostr_f  (const void* e) { return ""; }
static char* tostr_lf (const void* e) { return ""; }
static char* tostr_llf(const void* e) { return ""; }
static char* tostr_z  (const void* e) { return ""; }
static char* tostr_str(const void* e) { return ""; }
static char* tostr_ptr(const void* e) { return ""; }


static void copy_i8 (void* e1, const void* e2) { *(int8_t*) e1 = *(int8_t*) e2; }
static void copy_i16(void* e1, const void* e2) { *(int16_t*)e1 = *(int16_t*)e2; }
static void copy_i32(void* e1, const void* e2) { *(int32_t*)e1 = *(int32_t*)e2; }
static void copy_i64(void* e1, const void* e2) { *(int64_t*)e1 = *(int64_t*)e2; }
static void copy_u8 (void* e1, const void* e2) { *(int8_t*) e1 = *(int8_t*) e2; }
static void copy_u16(void* e1, const void* e2) { *(int16_t*)e1 = *(int16_t*)e2; }
static void copy_u32(void* e1, const void* e2) { *(int32_t*)e1 = *(int32_t*)e2; }
static void copy_u64(void* e1, const void* e2) { *(int64_t*)e1 = *(int64_t*)e2; }
static void copy_f  (void* e1, const void* e2) { *(float*)  e1 = *(float*)  e2; }
static void copy_lf (void* e1, const void* e2) { *(double*) e1 = *(double*) e2; }
static void copy_llf(void* e1, const void* e2) { *(long double*) e1 = *(long double*) e2; }
static void copy_z  (void* e1, const void* e2) { *(size_t*) e1 = *(size_t*) e2; }
static void copy_str(void* e1, const void* e2) { *(char**)e1 = strdup(*(char**)e2); }
static void copy_ptr(void* e1, const void* e2) { *(void**)e1 = *(void**)e2; }

/* -- Define trait structure -- */

#define DECLARE_TRAIT_STRUCT(_t) \
	static ax_basic_trait_t trait_##_t = { \
		.type = type_##_t, \
		.size = size_##_t, \
		.equal = equal_##_t, \
		.less = less_##_t, \
		.hash = hash_##_t, \
		.free = free_##_t, \
		.copy = copy_##_t, \
		.tostr = tostr_##_t \
	};

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
const ax_basic_trait_t* ax_basic_get_trait(ax_basic_type_t type)
{
	switch(type) {
		case AX_BT_I8:   return &trait_i8;
		case AX_BT_I16:  return &trait_i16;
		case AX_BT_I32:  return &trait_i32;
		case AX_BT_I64:  return &trait_i64;
		case AX_BT_U8:   return &trait_u8;
		case AX_BT_U16:  return &trait_u16;
		case AX_BT_U32:  return &trait_u32;
		case AX_BT_U64:  return &trait_u64;
		case AX_BT_Z:    return &trait_f;
		case AX_BT_F:    return &trait_lf;
		case AX_BT_LF:   return &trait_llf;
		case AX_BT_LLF:  return &trait_z;
		case AX_BT_STR:  return &trait_str;
		case AX_BT_PTR:  return &trait_ptr;
		case AX_BT_RAW:  return NULL;
		default:         return NULL;
	}
}

//void ax_basic_init(void)
//{
//	init_trait();
//}
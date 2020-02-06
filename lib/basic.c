#include "basic.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
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
		case AX_BT_F:    return sizeof(float);
		case AX_BT_LF:   return sizeof(double);
		case AX_BT_LLF:  return sizeof(long double);
		case AX_BT_STR:
		case AX_BT_PTR:
		default:         return 0;
	}
}


void ax_basic_va_read(ax_basic_type_t type, ax_basic_t* basic, va_list arg)
{
	ax_assert(type<AX_BT_RAW, "Unsupport type '%s'(%d)", ax_basic_name(type), type);
	va_list va;
	va_copy(va, arg);
	switch(type) {
		case AX_BT_I8:  basic->i8 =  (int8_t)va_arg(va, int32_t); break;
		case AX_BT_I16: basic->i16 = (int16_t)va_arg(va, int32_t); break;
		case AX_BT_I32: basic->i32 = va_arg(va, int32_t); break;
		case AX_BT_I64: basic->u64 = va_arg(va, int64_t); break;
		case AX_BT_U8:  basic->u8 =  (uint8_t)va_arg(va, uint32_t); break;
		case AX_BT_U16: basic->u16 = (uint16_t)va_arg(va, uint32_t); break;
		case AX_BT_U32: basic->u32 = va_arg(va, uint32_t); break;
		case AX_BT_U64: basic->u64 = va_arg(va, uint64_t); break;
		case AX_BT_F:   basic->f =   (float)va_arg(va, double); break;
		case AX_BT_LF:  basic->lf =  va_arg(va, double); break;
		case AX_BT_LLF: basic->llf = va_arg(va, long double); break;
		case AX_BT_STR: basic->str = va_arg(va, void*); break;
		case AX_BT_PTR: basic->ptr = va_arg(va, void*); break;
	}
	va_end(va);
}

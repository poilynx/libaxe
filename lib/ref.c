#include "ref.h"
#include <stdio.h>
#include <stdlib.h>
static char* ref_name(char type)
{
	switch(type) {
		case AX_RT_I8:   return "int8_t";
		case AX_RT_I16:  return "int16_t";
		case AX_RT_I32:  return "int32_t";
		case AX_RT_I64:  return "int64_t";
		case AX_RT_U8:   return "uint8_t";
		case AX_RT_U16:  return "uint16_t";
		case AX_RT_U32:  return "uint32_t";
		case AX_RT_U64:  return "uint64_t";
		case AX_RT_F:    return "float";
		case AX_RT_LF:   return "double";
		case AX_RT_LLF:  return "long_double";
		case AX_RT_STR:  return "char*";
		case AX_RT_PTR:  return "void*";
		case AX_RT_BOX:  return "box";
		default:         return "unknow_type";
	}
}


size_t ax_ref_size(unsigned char type)
{
	switch(type) {
		case AX_RT_I8:   return sizeof(int8_t);
		case AX_RT_I16:  return sizeof(int16_t);
		case AX_RT_I32:  return sizeof(int32_t);
		case AX_RT_I64:  return sizeof(int64_t);
		case AX_RT_U8:   return sizeof(uint8_t);
		case AX_RT_U16:  return sizeof(uint16_t);
		case AX_RT_U32:  return sizeof(uint32_t);
		case AX_RT_U64:  return sizeof(uint64_t);
		case AX_RT_F:    return sizeof(float);
		case AX_RT_LF:   return sizeof(double);
		case AX_RT_LLF:  return sizeof(long double);
		case AX_RT_STR:
		case AX_RT_PTR:
		case AX_RT_BOX:  return sizeof(void*);
		default:         return 0;
	}
}

static inline void check(char* f, char src, char dst)
{
#ifndef NDEBUG
	if(src != dst) {
		static const char* errfmt = "%s: invalid conversion from '%s' to '%s'";
		fprintf(stderr, errfmt, f, ref_name(src), ref_name(dst));
		abort();
	}
#endif
}

int8_t   ax_ref_toi8 (ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_I8);    return *(int8_t*)r.ptr;  }
int16_t  ax_ref_toi16(ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_I16);   return *(int16_t*)r.ptr; }
int32_t  ax_ref_toi32(ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_I32);   return *(int32_t*)r.ptr; }
int64_t  ax_ref_toi64(ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_I64);   return *(int64_t*)r.ptr; }
uint8_t  ax_ref_tou8 (ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_U8);    return *(uint8_t*)r.ptr; }
uint16_t ax_ref_tou16(ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_U16);   return *(uint16_t*)r.ptr;}
uint32_t ax_ref_tou32(ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_U32);   return *(uint32_t*)r.ptr;}
uint64_t ax_ref_tou64(ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_U64);   return *(uint64_t*)r.ptr;}
float    ax_ref_tof  (ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_FLOAT); return *(float*)r.ptr;   }
double   ax_ref_tolf (ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_DOUBLE);return *(double*)r.ptr;  }
void*    ax_ref_toptr(ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_PTR);   return (void*)r.ptr;     }
char*    ax_ref_tostr(ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_STR);   return (char*)r.ptr;     }
ax_box_t*ax_ref_tobox(ax_ref_t r) { check(__FUNCTION_, r.type, AX_RT_BOX);   return (ax_box_t*)r.ptr; }


void ax_ref_va_read(unsigned char type, ax_clip_t* clip, va_list arg)
{
	va_list va;
	va_copy(va, arg);
	switch(type) {
		case AX_RT_I8:   clip->i8 =  va_arg(va, int8_t); break;
		case AX_RT_I16:  clip->i16 = va_arg(va, int16_t); break;
		case AX_RT_I32:  clip->i32 = va_arg(va, int32_t); break;
		case AX_RT_I64:  clip->64 =  va_arg(va, int64_t); break;
		case AX_RT_U8:   clip->u8 =  va_arg(va, uint8_t); break;
		case AX_RT_U16:  clip->u16 = va_arg(va, uint16_t); break;
		case AX_RT_U32:  clip->u32 = va_arg(va, uint32_t); break;
		case AX_RT_U64:  clip->u64 = va_arg(va, uint64_t); break;
		case AX_RT_F:    clip->f =   va_arg(va, float); break;
		case AX_RT_LF:   clip->lf =  va_arg(va, double); break;
		case AX_RT_LLF:  clip->llf = va_arg(va, long double); break;
		case AX_RT_STR:  clip->str = va_arg(va, void*); break;
		case AX_RT_PTR:  clip->ptr = va_arg(va, void*); break;
		case AX_RT_BOX:  clip->box = va_arg(va, void$); break;
	}
	va_end(va);
}

#include "ref.h"
#include <stdio.h>
#include <stdlib.h>


static const char* errfmt = "%s: invalid conversion from '%s' to '%s'";
#define CHECK(src, dst) ax_assert(dst == src , errfmt, ax_basic_name(src), ax_basic_name(dst));

int8_t      ax_ref_toi8 (ax_ref_t r) { CHECK(r.type, AX_BT_I8);  return *(int8_t*)r.ptr;  }
int16_t     ax_ref_toi16(ax_ref_t r) { CHECK(r.type, AX_BT_I16); return *(int16_t*)r.ptr; }
int32_t     ax_ref_toi32(ax_ref_t r) { CHECK(r.type, AX_BT_I32); return *(int32_t*)r.ptr; }
int64_t     ax_ref_toi64(ax_ref_t r) { CHECK(r.type, AX_BT_I64); return *(int64_t*)r.ptr; }
uint8_t     ax_ref_tou8 (ax_ref_t r) { CHECK(r.type, AX_BT_U8);  return *(uint8_t*)r.ptr; }
uint16_t    ax_ref_tou16(ax_ref_t r) { CHECK(r.type, AX_BT_U16); return *(uint16_t*)r.ptr;}
uint32_t    ax_ref_tou32(ax_ref_t r) { CHECK(r.type, AX_BT_U32); return *(uint32_t*)r.ptr;}
uint64_t    ax_ref_tou64(ax_ref_t r) { CHECK(r.type, AX_BT_U64); return *(uint64_t*)r.ptr;}
float       ax_ref_tof  (ax_ref_t r) { CHECK(r.type, AX_BT_F);   return *(float*)r.ptr;   }
double      ax_ref_tolf (ax_ref_t r) { CHECK(r.type, AX_BT_LF);  return *(double*)r.ptr;  }
long double ax_ref_tollf(ax_ref_t r) { CHECK(r.type, AX_BT_LLF); return *(long double*)r.ptr;}
void*       ax_ref_toptr(ax_ref_t r) { CHECK(r.type, AX_BT_PTR); return *(void**)r.ptr;   }
char*       ax_ref_tostr(ax_ref_t r) { CHECK(r.type, AX_BT_STR); return (char*)r.ptr;     }
void*       ax_ref_toraw(ax_ref_t r) { CHECK(r.type, AX_BT_RAW); return r.ptr;            }



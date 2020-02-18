#include "ref.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>

static const char* errfmt = "%s: invalid conversion from '%s%s' to '%s%s'";
#define CHKTYPE(_t, _p) ax_assert( \
	_t == r.type, \
	errfmt, \
	ax_stuff_name(r.type), _p ? " *" : "", \
	ax_stuff_name(_t), _p ? " *" : "")

int8_t      ax_ref_i8 (ax_ref_t r) { CHKTYPE(AX_ST_I8 , 0); return *(int8_t*)r.ptr;  }
int16_t     ax_ref_i16(ax_ref_t r) { CHKTYPE(AX_ST_I16, 0); return *(int16_t*)r.ptr; }
int32_t     ax_ref_i32(ax_ref_t r) { CHKTYPE(AX_ST_I32, 0); return *(int32_t*)r.ptr; }
int64_t     ax_ref_i64(ax_ref_t r) { CHKTYPE(AX_ST_I64, 0); return *(int64_t*)r.ptr; }
uint8_t     ax_ref_u8 (ax_ref_t r) { CHKTYPE(AX_ST_U8,  0); return *(uint8_t*)r.ptr; }
uint16_t    ax_ref_u16(ax_ref_t r) { CHKTYPE(AX_ST_U16, 0); return *(uint16_t*)r.ptr;}
uint32_t    ax_ref_u32(ax_ref_t r) { CHKTYPE(AX_ST_U32, 0); return *(uint32_t*)r.ptr;}
uint64_t    ax_ref_u64(ax_ref_t r) { CHKTYPE(AX_ST_U64, 0); return *(uint64_t*)r.ptr;}
float       ax_ref_f  (ax_ref_t r) { CHKTYPE(AX_ST_F,   0); return *(float*)r.ptr;   }
double      ax_ref_lf (ax_ref_t r) { CHKTYPE(AX_ST_LF,  0); return *(double*)r.ptr;  }
long double ax_ref_llf(ax_ref_t r) { CHKTYPE(AX_ST_LLF, 0); return *(long double*)r.ptr;}
void*       ax_ref_ptr(ax_ref_t r) { CHKTYPE(AX_ST_PTR, 0); return *(void**)r.ptr;   }
char*       ax_ref_str(ax_ref_t r) { CHKTYPE(AX_ST_STR, 0); return (char*)r.ptr;     }

int8_t*     ax_ref_pi8 (ax_ref_t r) { CHKTYPE(AX_ST_I8 , 1); return (int8_t*)r.ptr;  }
int16_t*    ax_ref_pi16(ax_ref_t r) { CHKTYPE(AX_ST_I16, 1); return (int16_t*)r.ptr; }
int32_t*    ax_ref_pi32(ax_ref_t r) { CHKTYPE(AX_ST_I32, 1); return (int32_t*)r.ptr; }
int64_t*    ax_ref_pi64(ax_ref_t r) { CHKTYPE(AX_ST_I64, 1); return (int64_t*)r.ptr; }
uint8_t*    ax_ref_pu8 (ax_ref_t r) { CHKTYPE(AX_ST_U8,  1); return (uint8_t*)r.ptr; }
uint16_t*   ax_ref_pu16(ax_ref_t r) { CHKTYPE(AX_ST_U16, 1); return (uint16_t*)r.ptr;}
uint32_t*   ax_ref_pu32(ax_ref_t r) { CHKTYPE(AX_ST_U32, 1); return (uint32_t*)r.ptr;}
uint64_t*   ax_ref_pu64(ax_ref_t r) { CHKTYPE(AX_ST_U64, 1); return (uint64_t*)r.ptr;}
float*      ax_ref_pf  (ax_ref_t r) { CHKTYPE(AX_ST_F,   1); return (float*)r.ptr;   }
double*     ax_ref_plf (ax_ref_t r) { CHKTYPE(AX_ST_LF,  1); return (double*)r.ptr;  }
long double*ax_ref_pllf(ax_ref_t r) { CHKTYPE(AX_ST_LLF, 1); return (long double*)r.ptr;}
void**      ax_ref_pptr(ax_ref_t r) { CHKTYPE(AX_ST_PTR, 1); return (void**)r.ptr;   }
void*       ax_ref_raw (ax_ref_t r) { CHKTYPE(AX_ST_RAW, 1); return r.ptr;           }


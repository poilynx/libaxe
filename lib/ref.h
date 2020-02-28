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

#ifndef REF_H_
#define REF_H_
#include "def.h"
#include "stuff.h"
#include "debug.h"
#include <stdarg.h>
struct ax_ref_st
{
	void *ptr;
#ifdef AX_DEBUG
	char d_type;
#endif
};
typedef struct ax_ref_st ax_ref_t;

#ifdef AX_DEBUG
# define ax_ref_make(_p, _t) (struct ax_ref_st){ _p, _t }
# define ax_ref_check(_r, _t) ax_panic_if((r).d_type != (_t), AX_LM_ERROR, ax_strtab.uncompatable_type)
#else
# define ax_ref_check(_r, _t) ((void)0)
# define ax_ref_inizer(_p, _t) (struct ax_ref_st){ _p }
#endif

inline static void     ax_rget_nil(ax_ref_t r) { ax_ref_check(r, AX_ST_NIL); return (void)0; }
inline static int8_t   ax_rget_i8 (ax_ref_t r) { ax_ref_check(r, AX_ST_I8 ); return *(int8_t*)r.ptr; }
inline static int16_t  ax_rget_i16(ax_ref_t r) { ax_ref_check(r, AX_ST_I16); return *(int16_t*)r.ptr; }
inline static int32_t  ax_rget_i32(ax_ref_t r) { ax_ref_check(r, AX_ST_I32); return *(int32_t*)r.ptr; }
inline static int64_t  ax_rget_i64(ax_ref_t r) { ax_ref_check(r, AX_ST_I64); return *(int64_t*)r.ptr; }
inline static uint8_t  ax_rget_u8 (ax_ref_t r) { ax_ref_check(r, AX_ST_U8 ); return *(uint8_t*)r.ptr; }
inline static uint16_t ax_rget_u16(ax_ref_t r) { ax_ref_check(r, AX_ST_U16); return *(uint16_t*)r.ptr; }
inline static uint32_t ax_rget_u32(ax_ref_t r) { ax_ref_check(r, AX_ST_U32); return *(uint32_t*)r.ptr; }
inline static uint64_t ax_rget_u64(ax_ref_t r) { ax_ref_check(r, AX_ST_U64); return *(uint64_t*)r.ptr; }
inline static size_t   ax_rget_z  (ax_ref_t r) { ax_ref_check(r, AX_ST_Z  ); return *(size_t*)r.ptr; }
inline static float    ax_rget_f  (ax_ref_t r) { ax_ref_check(r, AX_ST_F  ); return *(float*)r.ptr; }
inline static double   ax_rget_lf (ax_ref_t r) { ax_ref_check(r, AX_ST_LF ); return *(double*)r.ptr; }
inline static longd_t  ax_rget_llf(ax_ref_t r) { ax_ref_check(r, AX_ST_LLF); return *(longd_t*)r.ptr; }
inline static char*    ax_rget_str(ax_ref_t r) { ax_ref_check(r, AX_ST_STR); return (char*)r.ptr; }
inline static void*    ax_rget_ptr(ax_ref_t r) { ax_ref_check(r, AX_ST_PTR); return *(void**)r.ptr; }
inline static void*    ax_rget_raw(ax_ref_t r) { ax_ref_check(r, AX_ST_RAW); return r.ptr; }
inline static void*    ax_rget_pwl(ax_ref_t r, char l) { ax_ref_check(r, ax_stuff_pwl(l)); ; return *(void**)r.ptr; }

inline static ax_ref_t ax_rset_nil(void       ) { return ax_ref_make(0, AX_ST_I8 ); }
inline static ax_ref_t ax_rset_i8 (int8_t*   p) { return ax_ref_make(p, AX_ST_I16); }
inline static ax_ref_t ax_rset_i16(int16_t*  p) { return ax_ref_make(p, AX_ST_I16); }
inline static ax_ref_t ax_rset_i32(int32_t*  p) { return ax_ref_make(p, AX_ST_I32); }
inline static ax_ref_t ax_rset_i64(int64_t*  p) { return ax_ref_make(p, AX_ST_I64); }
inline static ax_ref_t ax_rset_u8 (uint8_t*  p) { return ax_ref_make(p, AX_ST_U8 ); }
inline static ax_ref_t ax_rset_u16(uint16_t* p) { return ax_ref_make(p, AX_ST_U16); }
inline static ax_ref_t ax_rset_u32(uint32_t* p) { return ax_ref_make(p, AX_ST_U32); }
inline static ax_ref_t ax_rset_u64(uint64_t* p) { return ax_ref_make(p, AX_ST_U64); }
inline static ax_ref_t ax_rset_z  (size_t*   p) { return ax_ref_make(p, AX_ST_Z  ); }
inline static ax_ref_t ax_rset_f  (float*    p) { return ax_ref_make(p, AX_ST_F  ); }
inline static ax_ref_t ax_rset_lf (double*   p) { return ax_ref_make(p, AX_ST_LF ); }
inline static ax_ref_t ax_rset_llf(longd_t*  p) { return ax_ref_make(p, AX_ST_LLF); }
inline static ax_ref_t ax_rset_str(char*     p) { return ax_ref_make(p, AX_ST_STR); }
inline static ax_ref_t ax_rset_ptr(void**    p) { return ax_ref_make(p, AX_ST_PTR); }
inline static ax_ref_t ax_rset_raw(void*     p) { return ax_ref_make(p, AX_ST_RAW); }
inline static ax_ref_t ax_rset_pwl(void**    p, char l) { return ax_ref_make(p, ax_stuff_pwl(l)); }

#define ax_rget_nil(_r) (ax_step(ax_rget_nil), ax_rget_nil((_r))) 
#define ax_rget_raw(_r) (ax_step(ax_rget_raw), ax_rget_raw((_r)))
#define ax_rget_i8 (_r) (ax_step(ax_rget_i8 ), ax_rget_i8 ((_r)))
#define ax_rget_i16(_r) (ax_step(ax_rget_i16), ax_rget_i16((_r)))
#define ax_rget_i32(_r) (ax_step(ax_rget_i32), ax_rget_i32((_r)))
#define ax_rget_i64(_r) (ax_step(ax_rget_i64), ax_rget_i64((_r)))
#define ax_rget_u8 (_r) (ax_step(ax_rget_u8 ), ax_rget_u8 ((_r)))
#define ax_rget_u16(_r) (ax_step(ax_rget_u16), ax_rget_u16((_r)))
#define ax_rget_u32(_r) (ax_step(ax_rget_u32), ax_rget_u32((_r)))
#define ax_rget_u64(_r) (ax_step(ax_rget_u64), ax_rget_u64((_r)))
#define ax_rget_z  (_r) (ax_step(ax_rget_z  ), ax_rget_z  ((_r)))
#define ax_rget_f  (_r) (ax_step(ax_rget_f  ), ax_rget_f  ((_r)))
#define ax_rget_lf (_r) (ax_step(ax_rget_lf ), ax_rget_lf ((_r)))
#define ax_rget_llf(_r) (ax_step(ax_rget_llf), ax_rget_llf((_r)))
#define ax_rget_str(_r) (ax_step(ax_rget_str), ax_rget_str((_r)))
#define ax_rget_ptr(_r) (ax_step(ax_rget_ptr), ax_rget_ptr((_r)))

#endif

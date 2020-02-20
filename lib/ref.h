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
#include <stdarg.h>
struct ax_ref_st
{
	void *ptr;
	char type;
};
typedef struct ax_ref_st ax_ref_t;

int8_t      ax_ref_i8 (ax_ref_t r);
int16_t     ax_ref_i16(ax_ref_t r);
int32_t     ax_ref_i32(ax_ref_t r);
int64_t     ax_ref_i64(ax_ref_t r);
uint8_t     ax_ref_u8 (ax_ref_t r);
uint16_t    ax_ref_u16(ax_ref_t r);
uint32_t    ax_ref_u32(ax_ref_t r);
uint64_t    ax_ref_u64(ax_ref_t r);
float       ax_ref_f  (ax_ref_t r);
double      ax_ref_lf (ax_ref_t r);
long double ax_ref_llf(ax_ref_t r);
void*       ax_ref_ptr(ax_ref_t r);
char*       ax_ref_str(ax_ref_t r);

int8_t*      ax_ref_pi8 (ax_ref_t r);
int16_t*     ax_ref_pi16(ax_ref_t r);
int32_t*     ax_ref_pi32(ax_ref_t r);
int64_t*     ax_ref_pi64(ax_ref_t r);
uint8_t*     ax_ref_pu8 (ax_ref_t r);
uint16_t*    ax_ref_pu16(ax_ref_t r);
uint32_t*    ax_ref_pu32(ax_ref_t r);
uint64_t*    ax_ref_pu64(ax_ref_t r);
float*       ax_ref_pf  (ax_ref_t r);
double*      ax_ref_plf (ax_ref_t r);
long double* ax_ref_pllf(ax_ref_t r);
void**       ax_ref_pptr(ax_ref_t r);
void*        ax_ref_raw (ax_ref_t r);

#endif

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

#ifndef AXE_H_
#define AXE_H_
#include "def.h"
#include "iter.h"
#include "box.h"
void ax__init(bool debug, bool trace);
void ax__uninit();

#ifdef AX_TRACE
# define AX__TRACE_ENABLE 1
#else
# define AX__TRACE_ENABLE 0
#endif

#ifdef AX_DEBUG
# define AX__DEBUG_ENABLE 1
#else
# define AX__DEBUG_ENABLE 0
#endif

#define ax_init()   ax__init(AX__DEBUG_ENABLE, AX__TRACE_ENABLE)
#define ax_uninit() ax__uninit()

#define ax_foreach(_r, _a) \
	for ( char __for_flag = 1 ; __for_flag ; ) \
	for ( ax_ref _r ; __for_flag ; __for_flag = 0) \
	for ( \
		ax_iter _it = ax_box_begin((_a)), __##_it##_end = ax_box_end((_a)); \
		!ax_iter_equal(&(_it), &(__##_it##_end)) && ((_r) = ax_iter_get(&_it, 0), 1); \
		ax_iter_shift(&_it, 1) \
	)

#endif

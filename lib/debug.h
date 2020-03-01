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

#ifndef DEBUG_H_
#define DEBUG_H_
#include <stddef.h>
#include <stdio.h>
/* --- For this library --- */

#define AX_LM_INFO     0
#define AX_LM_WARNING  1
#define AX_LM_ERROR    2
int  ax_debug_trace;
void ax_debug_set_fd (FILE* fp);
void ax_debug_pwhere ();
void ax_debug_step (const char* file, const char* caller, int line, const char* callee);
void ax_debug_log (int level, const char*, ...);
void ax_debug_abort ();
void ax_debug_assert_fail (const char* file, const char* func, int line, const char* brief, const char* fmt, ...);

#define ax_abort ax_debug_abort

#ifdef AX_DEBUG
#define ax_pinfo(_f, ...)             (ax_debug_trace ? ax_debug_log(AX_LM_INFO, (_f), ##__VA_ARGS__) : (void)0)
#define ax_pwarning(_f, ...)          (ax_debug_trace ? ax_debug_log(AX_LM_WARNING, (_f), ##__VA_ARGS__) : (void)0)
#define ax_perror(_f, ...)            (ax_debug_trace ? ax_debug_log(AX_LM_ERROR, (_f), ##__VA_ARGS__) : (void)0)
#define ax_pinfo_if(_c, _f, ...)      ((ax_debug_trace && (_c)) ? ax_debug_log(LOG_INFO, (_f), ##__VA_ARGS__) : (void)0)
#define ax_pwarning_if(_c, _f, ...)   ((ax_debug_trace && (_c)) ? ax_debug_log(LOG_WARN, (_f), ##__VA_ARGS__) : (void)0)
#define ax_perror_if(_c, _f, ...)     ((ax_debug_trace && (_c)) ? ax_debug_log(LOG_ERROR, (_f), ##__VA_ARGS__) : (void)0)
#define ax_panic_if(_c, _lm, _f, ...) (ax_debug_trace \
		? ((_c) ? ax_debug_log((_lm), (_f), ##__VA_ARGS__), ax_abort(): (void)0) \
		: ((_c) ? ax_abort(): (void)0))
#else
#define ax_pinfo(_f, ...)             (void)0
#define ax_pwarning(_f, ...)          (void)0
#define ax_perror(_f, ...)            (void)0
#define ax_pinfo_if(_c, _f, ...)      (void)0
#define ax_pwarn_if(_c, _f, ...)      (void)0
#define ax_perror_if(_c, _f, ...)     (void)0
#define ax_panic_if(_c, _lm, _f, ...) (void)0
#endif

#ifdef AX_TRACE
# define ax_step(__c) ax_debug_step(__FILE__, __FUNCTION__, __LINE__, #__c)
#else
# define ax_step(__c) ((void)0)
#endif

#undef ax_assert
#ifdef AX_DEBUG
# define ax_assert(__e, __f, ...) ((__e) \
	? (void)0 : ax_debug_assert_fail(__FILE__, __FUNCTION__, __LINE__, "assertion failed", __f, ##__VA_ARGS__))
#else
# define ax_assert(__e, __f, ...) ((void)0)
#endif

#endif

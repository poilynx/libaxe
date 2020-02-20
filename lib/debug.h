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
void ax__ptrace(const char*, const char*, int, const char*);
void ax__fault(const char*, const char*, int, const char*, const char*, ...);

#undef ax_assert
#ifdef AX_NO_DEBUG
# define ax_assert(__e, __f) ((void)0)
#else
# define ax_assert(__e, __f, ...) ((__e) \
	? (void)0 : ax__fault(__FILE__, __FUNCTION__, __LINE__, "assertion failed", __f, ##__VA_ARGS__))
#endif

#undef ax_ptrace
#ifndef AX_TRACE
# define ax_ptrace(__c) ((void)0)
#else
# define ax_ptrace(__c) ax__ptrace(__FILE__, __FUNCTION__, __LINE__, #__c)
#endif

#undef ax_fault
#define ax_fault(__f, ...) (ax__fault(__FILE__,  __FUNCTION__,__LINE__, "error", __f, ##__VA_ARGS__))


#endif

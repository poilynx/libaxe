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

#include "debug.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void ax__fault(const char* file, const char* func, int line, const char* brief, const char* fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);

	char err[512];
	vsnprintf(err, sizeof(err), fmt, vl);
	fprintf(stderr, "ax:fault:%s:%s:%d:%s: %s\n", file, func, line, brief, err);

	va_end(vl);

	abort();
}

void ax__ptrace(const char* file, const char* func, int line, const char* call)
{
	fprintf(stderr, "ax:trace:%s:%s:%d: call %s\n", file, func, line, call);
}


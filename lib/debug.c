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
#include <string.h>

struct ax_where_st {
	const char* file;
	const char* caller;
	const char* callee;
	int line;
};

static struct ax_where_st g_where;
static FILE* g_fp = NULL;

int ax_debug_trace = 0;

void ax_debug_set_fd(FILE* fp)
{
	g_fp = fp;
}

void ax_debug_pwhere()
{
	if(!g_fp) return ;
	fprintf(g_fp, "%s:%s:%d:%s:",
			g_where.file,
			g_where.caller,
			g_where.line,
			g_where.callee);
}

void ax_debug_step(const char* file, const char* caller, int line, const char* callee)
{
	g_where.file = file;
	g_where.caller = caller;
	g_where.callee = callee;
	g_where.line = line;
}

void ax_debug_log(int level, const char* fmt, ...)
{
	if(!g_fp) return ;
	va_list vl;
	va_start(vl, fmt);
	char log_level[32];
	switch(level)
	{
		case AX_LM_INFO:    strcpy(log_level, "info"); break;
		case AX_LM_WARNING: strcpy(log_level, "warning"); break;
		case AX_LM_ERROR:   strcpy(log_level, "error"); break;
		default:            sprintf(log_level, "log<%d>", level); break;
	}

	fputs("ax:", g_fp);
	ax_debug_pwhere();
	fputs(log_level, g_fp);
	fputc(':', g_fp);
	vfprintf(g_fp, fmt, vl);
	fputc('\n', g_fp);

	va_end(vl);
}

void ax_debug_abort()
{
	if(g_fp) {
		fputs("ax:", g_fp);
		ax_debug_pwhere();
		fputs("abort\n", g_fp);
	}
	exit(-1);
}

void ax_debug_assert_fail(const char* file, const char* func, int line, const char* brief, const char* fmt, ...)
{
	va_list vl;
	va_start(vl, fmt);

	fprintf(stderr, "%s:%s:%d:%s:", file, func, line, brief);
	fprintf(stderr, fmt, vl);
	fputc('\n', stderr);

	va_end(vl);

	abort();
}

#include "debug.h"
#include <stderr.h>
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


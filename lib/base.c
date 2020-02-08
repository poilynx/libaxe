#include "base.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void __ax_fault(const char* file, int line, const char* func, const char* brief, const char* fmt, ...)
{
	char err[256];
	va_list vl;
	va_start(vl, fmt);
	vsnprintf(err, sizeof(err), fmt, vl);
	fprintf(stderr, "%s:%s:%d: %s: %s\n", file, func, line, brief, err);
	va_end(vl);
	abort();
}

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
	fprintf(stderr, "%s#%d: %s: %s, in %s\n", func, line, brief, err, file);
	va_end(vl);
	abort();
}

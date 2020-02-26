#include "axe.h"
#include "debug.h"
#include <stdio.h>
void ax__init(int trace)
{
	ax_debug_trace = trace;
	ax_debug_set_fd(stdout);
}

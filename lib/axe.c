#include "axe.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>

static int init_count = 0;

void ax__init(ax_bool_t debug, ax_bool_t trace)
{
	if (init_count > 0) {
		if(init_count > 0xFFFF) {
			ax_perror("Too many times to initialize");
		} else
			init_count ++;
		return;
	}
#ifdef AX_DEBUG
	ax_bool_t lib_debug = ax_true;
#else
	ax_bool_t lib_debug = ax_false;
#endif
	if (lib_debug != debug) {
		if (debug)
			fputs("error:ax_init:program defined macro AX_DEBUG, but axe library did not\n", stderr);
		else
			fputs("error:ax_init:program did not define macro AX_DEBUG, but axe library did\n", stderr);
		exit(EXIT_FAILURE);
	}
	ax_debug_set_fd(stdout);
	ax_debug_trace = trace;
	init_count++;
}

void ax__uninit()
{
	if(init_count > 1) {
		
		init_count--;
		return;
	} else if (init_count == 0)
		return;
	ax_debug_set_fd(NULL);
	ax_debug_trace = ax_false;
	init_count--;
}

int ax__init_count()
{
	return init_count;
}

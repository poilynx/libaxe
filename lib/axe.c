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

#include "axe.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>

static int init_count = 0;

void ax__init(bool debug, bool trace)
{
	if (init_count > 0) {
		if(init_count > 0xFFFF) {
			ax_perror("Too many times to initialize");
		} else
			init_count ++;
		return;
	}
#ifdef AX_DEBUG
	bool lib_debug = true;
#else
	bool lib_debug = ax_false;
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
	ax_debug_trace = false;
	init_count--;
}

int ax__init_count()
{
	return init_count;
}

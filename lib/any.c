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

#include "any.h"
#include "stuff.h"
#include "debug.h"
#include <stdio.h>
#include <stdlib.h>

bool ax_IS(const ax_any* any, char type)
{
	switch(any->tr->type) {
		case AX_T_ANY:
			switch(type) {
				case AX_T_ANY: break;
				default: return false;
			}
		case AX_T_BOX: 
			switch(type) {
				case AX_T_ANY:
				case AX_T_BOX: break;
				default: return false;
			}
		case AX_T_MAP:
			switch(type) {
				case AX_T_ANY:
				case AX_T_BOX:
				case AX_T_MAP: break;
				default: return false;
			}
		case AX_T_SEQ:
			switch(type) {
				case AX_T_ANY:
				case AX_T_BOX:
				case AX_T_SEQ: break;
				default: return false;
			}
	}
	return true;

}

const char* ax_type_name(char type)
{
	switch(type) {
		case AX_T_ANY: return "!any";
		case AX_T_BOX: return "!any.box";
		case AX_T_SEQ: return "!any.box.seq";
		case AX_T_MAP: return "!any.box.map";
		default: return "unknow";
	}
}

static bool stuff_equal(const void* e1, const void* e2)
{
	return (void*)e1 == (void*)e2;
}

static bool stuff_less(const void* e1, const void* e2)
{
	return(void*)e1 < (void*)e2;
}

static void stuff_free(const void* e)
{
	ax_any* any = (ax_any*)e;
	any->tr->free(any);
}

static size_t stuff_hash(const void* e)
{
	return (size_t)*(void**)e;
}

static char* stuff_text(const void* e)
{
	char*buf = malloc(20);
	sprintf(buf, "0x%lX", *(long unsigned int*)e);
	return buf;
}

static void stuff_copy(void* dst, const void* src)
{
	ax_any* anys = *(ax_any**)src;
	*(void**)dst = anys->tr->copy(src);
}

static ax_stuff_trait any_stuff_trait = {
	.equal = stuff_equal,
	.less = stuff_less,
	.hash = stuff_hash,
	.free = stuff_free,
	.copy = stuff_copy,
	.text = stuff_text 
};

ax_stuff_trait* ax_any_stuff_trait()
{
	return &any_stuff_trait;
}


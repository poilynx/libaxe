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

#ifndef VAIL_H_
#define VAIL_H_
#include "def.h"
#include "stuff.h"
#include <stdint.h>
#include <stddef.h>
struct ax_vaf_item_st
{
	char type;
	char mut;
};
typedef struct ax_vaf_item_st ax_vaf_item_t;

struct ax_vaf_st
{
	char magic;
	char argc;
	ax_vaf_item_t table[0];
};
typedef struct ax_vaf_st ax_vaf_t;

struct ax_vail_node_st
{
	char mut;
	char type;
	ax_stuff_t value;
	size_t size;
	struct ax_vail_node_st* next;
};
typedef struct ax_vail_node_st ax_vail_node_t;

#define ax_vail_node_set(p, m, t, v, s) \
	((p)->mut = (m), \
	(p)->type = (t), \
	(p)->value = (v), \
	(p)->size = (s)) 


struct ax_vail_st
{
	size_t size;
	size_t capacity;
	struct ax_vail_node_st* head;
	struct ax_vail_node_st* tail;
};
typedef struct ax_vail_st ax_vail_t;

ax_vaf_t* ax_vaf_make(char *fmt);
void ax_vail_push(ax_vail_t* vail, ax_vail_node_t* node);
ax_vail_node_t* ax_vail_pop(ax_vail_t* vail);
ax_vail_t* ax_vail_read(ax_vaf_t* vaf, ...);

#endif

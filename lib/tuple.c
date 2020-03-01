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

#include "tuple.h"
#include "vail.h"
#include "stuff.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

ax_tuple* ax_tuple_make(ax_vail* vail)
{
	ax_tuple* t = malloc(sizeof(ax_tuple));
	t->table = malloc(sizeof(ax_tuple_item) * vail->size);
	t->stash = malloc(vail->capacity);
	t->size = vail->size;

	void* stash_pos = t->stash;
	ax_vail_node* node = vail->head;
	size_t i;
	for (i=vail->size-1; node; node=node->next, i--) {
		t->table[i].ptr = stash_pos;
		t->table[i].type = node->type;
		if (node->mut) {
			t->table[i].flag = AX_TF_MUTABLE;
			t->table[i].count = node->size;
			memcpy(stash_pos, node->value.ptr, node->size);
			stash_pos += node->size;
		} else {
			t->table[i].flag = 0;
			t->table[i].count = 1;
			memcpy(stash_pos, &(node->value), node->size);
			stash_pos += node->size;
		}
	}
	return t;
}

void ax_tuple_free(ax_tuple* t)
{
	assert(t);
	free(t->table);
	free(t->stash);
	free(t);
}


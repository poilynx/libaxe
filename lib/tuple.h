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

#ifndef TUPLE_H_
#define TUPLE_H_
#include "stuff.h"
#define AX_TF_MUTABLE 0x01
struct ax_tuple_st;
typedef struct ax_tuple_st ax_tuple;
struct ax_vail_st;
typedef struct ax_vail_st ax_vail;
struct ax_tuple_item_st
{
	char   type;
	char   flag;
	size_t count;
	void*  ptr;
};
typedef struct ax_tuple_item_st ax_tuple_item;

struct ax_tuple_st
{
	size_t size;
	ax_tuple_item* table;
	void* stash;
};
typedef struct ax_tuple_st ax_tuple;

ax_tuple* ax_tuple_make(ax_vail* vail);
void ax_tuple_free(ax_tuple* t);

#endif

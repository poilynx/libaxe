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

#include "vector.h"
#include "iter.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void iter_shift(ax_iter_t* it, int i)
{
	ax_vector_t* vec = it->owner;
	long off = (i * (vec->elem_size));
	it->point += it->tr->norm ? + off : - off;
}

static ax_ref_t iter_get(const ax_iter_t* it, int i)
{
	ax_vector_t* vec = it->owner;
	ax_ref_t ref;
	ref.type = vec->seq.elem_tr->type;
	ref.ptr = it->point;
	return ref;
}

static ax_bool_t iter_equal(const ax_iter_t* it1, const ax_iter_t* it2)
{
	return it1->point == it2->point;
}

static ax_bool_t iter_less(const ax_iter_t* it1, const ax_iter_t* it2)
{
	return it1->tr->norm ? (it1->point < it2->point) : (it1->point > it2->point);
}

static size_t iter_dist(const ax_iter_t* it1, const ax_iter_t* it2)
{
	long dist = it1->point - it2->point;
	return it1->tr->norm ? dist : - dist;
}

static const ax_iter_trait_t iter_trait = {
	.norm = ax_true,
	.shift = iter_shift,
	.get = iter_get,
	.equal = iter_equal,
	.less = iter_less,
	.dist = iter_dist,
};

static const ax_iter_trait_t reverse_iter_trait = {
	.norm = ax_false,
	.shift = iter_shift,
	.get = iter_get,
	.equal = iter_equal,
	.less = iter_less,
	.dist = iter_dist,
};

static void any_free(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	free(vec->buffer);
	if(any->flags & AX_AF_NEED_FREE)
		free(any);
}

static void any_dump(const ax_any_t* any, int ind)
{
	printf("dump\n");
}

static ax_any_t* any_copy(const ax_any_t* any)
{

	ax_vector_t* vec = (ax_vector_t*)any;
	ax_vector_t* new = malloc(sizeof(ax_vector_t));
	memcpy(new, any, sizeof(ax_vector_t));
	new->buffer = malloc(vec->elem_size * vec->capacity);
	memcpy(new->buffer, vec->buffer, vec->elem_size * vec->size);
	return (ax_any_t*)new;
}

static ax_any_t* any_move(ax_any_t* any)
{
	ax_vector_t* old = (ax_vector_t*)any;
	ax_vector_t* new = NULL;
	if(old->seq.box.any.flags & AX_AF_NEED_FREE)
		new = old;
	else {
		new = malloc(sizeof(ax_vector_t));
		memcpy(new, old, sizeof(ax_vector_t));
		new->buffer = old->buffer;
		memcpy(new->buffer, old->buffer, old->elem_size * old->size);
		
		old->size = 0;
		old->buffer = NULL;
		old->seq.box.any.flags |= AX_AF_FREED;
	}
	return (ax_any_t*)new;

}

static size_t box_size(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	return vec->size;
}

static size_t box_maxsize(ax_any_t* any)
{
	return 1028;
}

static ax_iter_t box_begin(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	ax_iter_t it;
	it.owner = any;
	it.point = vec->buffer;
	it.tr = &iter_trait;
	return it;
}

static ax_iter_t box_end(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	ax_iter_t it;
	it.owner = any;
	it.point = vec->buffer + (vec->elem_size * vec->size);
	it.tr = &iter_trait;
	return it;
	
}

static ax_iter_t box_rbegin(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	ax_iter_t it;
	it.owner = any;
	it.point = vec->buffer + (vec->size - 1) * vec->elem_size;
	it.tr = &reverse_iter_trait;
	return it;
}

static ax_iter_t box_rend(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	ax_iter_t it;
	it.owner = any;
	it.point = vec->buffer - vec->elem_size;
	it.tr = &reverse_iter_trait;
	return it;
}

static ax_iter_t box_erase(ax_any_t* any, ax_iter_t* it)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	ax_assert(it->point >= vec->buffer && it->point < vec->buffer + vec->size*vec->elem_size, "bad iterator");
	 
	vec->seq.elem_tr->free(it->point);
	size_t end = vec->buffer + vec->size - vec->elem_size;
	for (void* p = it->point ; p < end ; p += vec->elem_size) {
		vec->seq.elem_tr->move(p, p + vec->elem_size);
	}
	vec->size --;
	if(!it->tr->norm)
		it->point -= vec->elem_size;

	return *it;
}

static void box_clear(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	ax_assert(it->point >= vec->buffer && it->point < vec->buffer + vec->size*vec->elem_size, "bad iterator");
	size_t end = vec->buffer + vec->size;
	for (void* p = it->point ; p < end ; p += vec->elem_size) {
		vec->seq.elem_tr->free(p, p + vec->elem_size);
	}
	free(vec->buffer);
	vec->size = 0;
	vec->capacity = 0;
}

static ax_bool_t seq_push(ax_any_t* any, void* e)
{
	ax_vector_t* vec = (ax_vector_t*)any;

	if (vec->size + 1 >= vec->capacity) {
		if(vec->capacity + 1 > vec->maxsize) {
			return ax_false;
		}
		vec->capacity += 100;
		if(vec->capacity > vec->maxsize)
			vec->capacity = vec->maxsize;
		vec->buffer = realloc(vec->buffer, vec->capacity * vec->elem_size);
	}
	vec->seq.elem_tr->copy(vec->buffer + (vec->size * vec->elem_size), e);
	vec->size ++;
	return ax_true;
}

static ax_bool_t seq_pop(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	if (vec->size == 0)
		return ax_false;
	vec->size --;
	return ax_true;
}

static void seq_sort(ax_any_t* any)
{
	printf("not implemented\n");
}

static const ax_any_trait_t any_treat = {
	.type = AX_T_SEQ,
	.name = "any_box_seq_vector",
	.free = any_free,
	.dump = any_dump,
	.copy = any_copy,
	.move = any_move,
};

static const ax_box_trait_t box_trait = {
	.size = box_size,
	.maxsize = box_maxsize,
	.begin = box_begin,
	.end = box_end,
	.rbegin = box_rbegin,
	.rend = box_rend,
	.erase = box_erase,
	.clear = box_clear
};

static const ax_seq_trait_t seq_trait = {
	.push = seq_push,
	.pop = seq_pop,
	.sort = seq_sort
};

ax_any_t* ax_vector_create(ax_vector_t* pt,const ax_stuff_trait_t* elem_tr)
{
	if (pt == NULL) {
		pt = malloc(sizeof(ax_vector_t));
		pt->seq.box.any.flags = AX_AF_NEED_FREE;
	}
	pt->seq.box.any.flags = 0;

	ax_any_t* any = &pt->seq.box.any;
	strcpy(any->magic, "AX");
	any->tr = &any_treat;

	ax_box_t* box = &pt->seq.box;
	box->tr = &box_trait;

	ax_seq_t* seq = &pt->seq;
	seq->tr = &seq_trait;
	seq->elem_tr = elem_tr;

	pt->maxsize = box->tr->maxsize(any);
	pt->buffer = NULL;
	pt->capacity = 0;
	pt->size = 0;
	pt->elem_size = elem_tr->size;

	return (ax_any_t*)pt;
}


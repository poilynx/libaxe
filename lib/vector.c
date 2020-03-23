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
#include "ref.h"
#include "any.h"
#include "iter.h"
#include "debug.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef AX_DEBUG
#define BEGIN_TRAIT(_a) ax_any_assert_type((_a), AX_T_SEQ); ax_vector* vec = (ax_vector*)_a;
#else
#define BEGIN_TRAIT(_a) ax_vector* vec = (ax_vector*)_a;

#endif

static bool    seq_push(ax_aseq* any, ax_cref elem);
static bool    seq_pop(ax_aseq* any);
static ax_iter seq_find(const ax_aseq* any, ax_cref elem);
static void    seq_sort(ax_aseq* any);

static void    box_clear(ax_any* any);
static size_t  box_size(const ax_abox* any);
static size_t  box_maxsize(const ax_abox* any);
static ax_iter box_begin(const ax_abox* any);
static ax_iter box_end(const ax_abox* abox);
static ax_iter box_rbegin(const ax_abox* abox);
static ax_iter box_rend(const ax_abox* abox);
static ax_iter box_erase(ax_abox* abox, ax_iter* it);

static void    any_free(ax_any* any);
static void    any_dump(const ax_any* any, int ind);
static ax_any* any_copy(const ax_any* any);
static ax_any* any_move(ax_any* any);

static void   iter_shift(ax_iter* it, int i);
static ax_ref iter_get(const ax_iter* it, int i);
static bool   iter_equal(const ax_iter* it1, const ax_iter* it2);
static bool   iter_less(const ax_iter* it1, const ax_iter* it2);
static size_t iter_dist(const ax_iter* it1, const ax_iter* it2);

static inline void check_two_iterator(const ax_iter* it1, const ax_iter* it2)
{
	ax_panic_if(it1->owner != it2->owner, AX_LM_ERROR, "inconsistent owner of two iterator");
	ax_panic_if(it1->tr != it2->tr, AX_LM_ERROR, "inconsistent direction of two iterator");
}

static void iter_shift(ax_iter* it, int i)
{
	const ax_vector* vec = it->owner;
	long off = (i * (vec->elem_size));
	it->point += it->tr->norm ? + off : - off;
}

static ax_ref iter_get(const ax_iter* it, int i)
{
	const ax_vector* vec = it->owner;
	ax_ref ref;
	ref.d_type = vec->seq.elem_tr->type;
	ref.ptr = it->point;
	return ref;
}


static bool iter_equal(const ax_iter* it1, const ax_iter* it2)
{
	check_two_iterator(it1, it2);
	return it1->point == it2->point;
}

static bool iter_less(const ax_iter* it1, const ax_iter* it2)
{
	check_two_iterator(it1, it2);
	return it1->tr->norm ? (it1->point < it2->point) : (it1->point > it2->point);
}

static size_t iter_dist(const ax_iter* it1, const ax_iter* it2)
{
	check_two_iterator(it1, it2);
	const ax_vector* vec = it1->owner;
	size_t len = (it1->point > it2->point)
		? it1->point - it2->point
		: it2->point - it1->point;
		return len / vec->elem_size;
}

static const ax_iter_trait iter_trait = {
	.norm = true,
	.shift = iter_shift,
	.get = iter_get,
	.equal = iter_equal,
	.less = iter_less,
	.dist = iter_dist,
};

static const ax_iter_trait reverse_iter_trait = {
	.norm = false,
	.shift = iter_shift,
	.get = iter_get,
	.equal = iter_equal,
	.less = iter_less,
	.dist = iter_dist,
};

static void any_free(ax_any* any)
{
	box_clear(any);
	if (!(any->flags & AX_AF_RENTED))
		free(any);
}

static void any_dump(const ax_any* any, int ind)
{
	printf("not implemented\n");
}

static ax_any* any_copy(const ax_any* any)
{
	BEGIN_TRAIT(any);
	ax_vector* new = malloc(sizeof(ax_vector));
	memcpy(new, any, sizeof(ax_vector));
	new->buffer = malloc(vec->elem_size * vec->capacity);
	memcpy(new->buffer, vec->buffer, vec->elem_size * vec->size);
	return (ax_any*)new;
}

static ax_any* any_move(ax_any* any)
{
	BEGIN_TRAIT(any);
	ax_vector* old = vec;
	ax_vector* new = NULL;
	if (!(old->seq.box.any.flags & AX_AF_RENTED))
		new = old;
	else {
		new = malloc(sizeof(ax_vector));
		memcpy(new, old, sizeof(ax_vector));
		new->buffer = old->buffer;
		memcpy(new->buffer, old->buffer, old->elem_size * old->size);
		
		old->size = 0;
		old->buffer = NULL;
		old->seq.box.any.flags |= AX_AF_FREED;
	}
	return (ax_any*)new;

}

static size_t box_size(const ax_abox* any)
{
	BEGIN_TRAIT(any);
	return vec->size;
}

static size_t box_maxsize(const ax_abox* any)
{
	return 1028;
}

static ax_iter box_begin(const ax_abox* any)
{
	BEGIN_TRAIT(any);
	ax_iter it;
	it.owner = any;
	it.point = vec->buffer;
	it.tr = &iter_trait;
	return it;
}

static ax_iter box_end(const ax_abox* any)
{
	BEGIN_TRAIT(any);
	ax_iter it;
	it.owner = any;
	it.point = vec->buffer + (vec->elem_size * vec->size);
	it.tr = &iter_trait;
	return it;
	
}

static ax_iter box_rbegin(const ax_abox* any)
{
	BEGIN_TRAIT(any);
	ax_iter it;
	it.owner = any;
	it.point = vec->buffer + (vec->size - 1) * vec->elem_size;
	it.tr = &reverse_iter_trait;
	return it;
}

static ax_iter box_rend(const ax_abox* any)
{
	BEGIN_TRAIT(any);
	ax_iter it;
	it.owner = any;
	it.point = vec->buffer - vec->elem_size;
	it.tr = &reverse_iter_trait;
	return it;
}

static ax_iter box_erase(ax_any* any, ax_iter* it)
{
	BEGIN_TRAIT(any);
	ax_panic_if(it->point < vec->buffer 
			|| it->point >= vec->buffer + vec->size*vec->elem_size,
			AX_LM_ERROR, "invalid iterator");
	 
	vec->seq.elem_tr->free(it->point);
	void* end = vec->buffer + (vec->size - 1) * vec->elem_size;
	for (void* p = it->point ; p < end ; p += vec->elem_size) {
		vec->seq.elem_tr->move(p, p + vec->elem_size);
	}
	vec->size --;
	if(!it->tr->norm)
		it->point -= vec->elem_size;

	return *it;
}

static void box_clear(ax_any* any)
{
	BEGIN_TRAIT(any);
	void* end = vec->buffer + vec->size;
	if (vec->buffer) {
		for (void* p = vec->buffer ; p < end ; p += vec->elem_size) {
			vec->seq.elem_tr->free(p);
		}
		free(vec->buffer);
		vec->buffer = NULL;
		vec->size = 0;
		vec->capacity = 0;
	}
}

static bool seq_push(ax_any* any, ax_cref elem)
{
	BEGIN_TRAIT(any);
	ax_cref_check(elem, vec->seq.elem_tr->type);
	if (vec->size + 1 >= vec->capacity) {
		if(vec->capacity + 1 > vec->maxsize) {
			ax_pwarning("has reached the maximum size of %hd", box_maxsize(any));
			return false;
		}
		vec->capacity += 100;
		if(vec->capacity > vec->maxsize)
			vec->capacity = vec->maxsize;
		vec->buffer = realloc(vec->buffer, vec->capacity * vec->elem_size);
		ax_pinfo("memory is realloced");
	}
	vec->seq.elem_tr->copy(vec->buffer + (vec->size * vec->elem_size), elem.ptr);
	vec->size ++;
	return true;
}

static bool seq_pop(ax_any* any)
{
	BEGIN_TRAIT(any);
	if (vec->size == 0)
	{
		ax_pinfo("nothing to pop");
		return false;
	}
	vec->size --;
	return true;
}

static void seq_sort(ax_any* any)
{
	printf("not implemented\n");
}


static void seq_invert(ax_any* any)
{
	BEGIN_TRAIT(any);
	size_t left = 0, right = vec->size - 1;
	void* tmp = malloc(vec->elem_size);
	while (right - left > 1) {
		vec->seq.elem_tr->move(tmp, vec->buffer + left * vec->elem_size);
		vec->seq.elem_tr->move(vec->buffer + right * vec->elem_size, vec->buffer + right * vec->elem_size);
		vec->seq.elem_tr->move(vec->buffer + right * vec->elem_size, tmp);
		left++, right--;
	}
}
static ax_iter seq_find(const ax_aseq* this, ax_cref elem)
{
	BEGIN_TRAIT(this);
	ax_cref_check(elem, vec->seq.elem_tr->type);
	ax_iter it = { .owner = vec, .tr = &iter_trait };
	void* end = vec->buffer + (vec->size - 1) * vec->elem_size;
	for (void* p = vec->buffer; p < end; p += vec->elem_size) {
		if(vec->seq.elem_tr->equal(elem.ptr, p)) {
			it.point = p;
			return it;
		}
	}
	it.point = end;
	return it;
}

static const ax_any_trait any_treat = {
	.type = AX_T_SEQ,
	.name = "any.box.seq:vector",
	.free = any_free,
	.dump = any_dump,
	.copy = any_copy,
	.move = any_move,
};

static const ax_box_trait box_trait = {
	.size = box_size,
	.maxsize = box_maxsize,
	.begin = box_begin,
	.end = box_end,
	.rbegin = box_rbegin,
	.rend = box_rend,
	.erase = box_erase,
	.clear = box_clear
};

static const ax_seq_trait seq_trait = {
	.push = seq_push,
	.pop = seq_pop,
	.sort = seq_sort,
	.find = seq_find,
	.invert = seq_invert
};

ax_any* ax_vector_create(ax_vector* pt,const ax_stuff_trait* elem_tr)
{
	if (pt == NULL)
		pt = malloc(sizeof(ax_vector));
	else
		pt->seq.box.any.flags = AX_AF_RENTED;
	
	pt->seq.box.any.flags = 0;

	ax_any* any = &pt->seq.box.any;
	ax_any_set_magic(any);
	any->tr = &any_treat;

	ax_box* box = &pt->seq.box;
	box->tr = &box_trait;

	ax_seq* seq = &pt->seq;
	seq->tr = &seq_trait;
	seq->elem_tr = elem_tr;

	pt->maxsize = box->tr->maxsize(any);
	pt->buffer = NULL;
	pt->capacity = 0;
	pt->size = 0;
	pt->elem_size = elem_tr->size;

	return (ax_any*)pt;
}


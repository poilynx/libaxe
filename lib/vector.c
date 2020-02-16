#include "vector.h"
#include "iter.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void iter_shift(ax_iter_t* it, int i)
{
	ax_vector_t* vec = it->owner;
	it->point += (i * (vec->seq.elem_tr->size()));
}

static ax_ref_t iter_get(const ax_iter_t* it, int i)
{
	ax_vector_t* vec = it->owner;
	ax_ref_t ref;
	ref.type = vec->seq.elem_tr->type();
	ref.ptr = it->point;
	return ref;
}

static ax_bool_t iter_equal(const ax_iter_t* it1, const ax_iter_t* it2)
{
	return it1->point == it2->point;
}

static ax_bool_t iter_less(const ax_iter_t* it1, const ax_iter_t* it2)
{

	return it1->point < it2->point;
}

static size_t iter_dist(const ax_iter_t* it1, const ax_iter_t* it2)
{
	return it2->point - it1->point;
}

static void iter_erase(ax_iter_t* it)
{
	ax_vector_t* vec = it->owner;
	vec->seq.box.tr->erase(it->owner, it);
}

static ax_iter_trait_t iter_trait = {
	.shift = iter_shift,
	.get = iter_get,
	.equal = iter_equal,
	.less = iter_less,
	.dist = iter_dist,
	.erase = iter_erase
};


static void riter_shift(ax_iter_t* it, int i)
{
	it->point -= i * ((ax_vector_t*)it->owner)->seq.elem_tr->size();
}

static ax_bool_t riter_less(const ax_iter_t* it1, const ax_iter_t* it2)
{

	return it1->point > it2->point;
}

static size_t riter_dist(const ax_iter_t* it1, const ax_iter_t* it2)
{
	return it1->point - it2->point;
}

static void riter_erase(ax_iter_t* it)
{
	ax_vector_t* vec = it->owner;
	vec->seq.box.tr->erase(it->owner, it);
	it->point --;
	
}

static ax_iter_trait_t reverse_iter_trait = {
	.shift = riter_shift,
	.get = iter_get,
	.equal = iter_equal,
	.less = riter_less,
	.dist = riter_dist,
	.erase = riter_erase
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

static char any_type(const ax_any_t* any)
{
	return AX_T_SEQ;
}

static ax_any_t* any_copy(const ax_any_t* any)
{

	ax_vector_t* vec = (ax_vector_t*)any;
	ax_vector_t* new = malloc(sizeof(ax_vector_t));
	memcpy(new, any, sizeof(ax_vector_t));
	size_t elem_size = vec->seq.elem_tr->size();
	new->buffer = malloc(elem_size * vec->capacity);
	memcpy(new->buffer, vec->buffer, elem_size * vec->size);
	return (ax_any_t*)new;
}

static ax_any_t* any_move(ax_any_t* any)
{
	//check freed
	ax_vector_t* old = (ax_vector_t*)any;
	ax_vector_t* new = NULL;
	if(old->seq.box.any.flags & AX_AF_NEED_FREE)
		new = old;
	else {
		new = malloc(sizeof(ax_vector_t));
		memcpy(new, old, sizeof(ax_vector_t));
		new->buffer = old->buffer;
		size_t elem_size = old->seq.elem_tr->size();
		memcpy(new->buffer, old->buffer, elem_size * old->size);
		
		old->size = 0;
		old->buffer = NULL;
		old->seq.box.any.flags |= AX_AF_FREED;
	}
#ifndef AX_NO_DEBUG
	new->seq.box.period ++;
#endif
	return (ax_any_t*)new;

}

static char* any_name(const ax_any_t* any)
{
	return "any_box_seq_vector";
}

static ax_any_trait_t any_treat = {
	.free = any_free,
	.dump = any_dump,
	.type = any_type,
	.copy = any_copy,
	.move = any_move,
	.name = any_name
};


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
	it.point = vec->buffer + (vec->size * vec->seq.elem_tr->size());
	it.tr = &iter_trait;
	return it;
	
}

static ax_iter_t box_rbegin(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	ax_iter_t it;
	it.owner = any;
	it.point = vec->buffer + vec->size - vec->seq.elem_tr->size();
	it.tr = &reverse_iter_trait;
	return it;
}

static ax_iter_t box_rend(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	ax_iter_t it;
	it.owner = any;
	it.point = vec->buffer - vec->seq.elem_tr->size();
	it.tr = &reverse_iter_trait;
	return it;
}

static ax_box_trait_t box_trait = {
	.size = box_size,
	.maxsize = box_maxsize,
	.begin = box_begin,
	.end = box_end,
	.rbegin = box_rbegin,
	.rend = box_rend
};

static ax_bool_t seq_push(ax_any_t* any, void* e)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	size_t elem_size = vec->seq.elem_tr->size();

	if (vec->size + 1 >= vec->capacity) {
		size_t max = vec->seq.box.tr->maxsize(any);
		if(vec->capacity + 1 > max) {
			return ax_false;
		}
		vec->capacity += 100;
		if(vec->capacity > max)
			vec->capacity = max;
		vec->buffer = realloc(vec->buffer, vec->capacity * elem_size);
	}
	vec->seq.elem_tr->copy(vec->buffer + (vec->size * elem_size), e);
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

static ax_seq_trait_t seq_trait = {
	.push = seq_push,
	.pop = seq_pop,
	.sort = seq_sort
};

ax_any_t* ax_vector_create(ax_vector_t* pt,const ax_basic_trait_t* elem_tr)
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

	pt->maxsize = 1028;
	//pt->elem_size = type == AX_BT_RAW ? raw_size : ax_basic_size(type);
	pt->buffer = NULL;//malloc(10 * pt->seq.elem_tr->size());
	pt->capacity = 0;//10;
	pt->size = 0;

	return (ax_any_t*)pt;
}


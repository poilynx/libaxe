#include "vector.h"
#include "iter.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>


static void any_free(ax_any_t* any)
{
	
}

static void any_dump(const ax_any_t* any, int ind)
{

}

static char any_type(const ax_any_t* any)
{

}

static ax_any_t* any_copy(const ax_any_t* any)
{

}

static ax_any_t* any_move(ax_any_t* any)
{

}

static char* any_name(const ax_any_t* any)
{

}

static ax_any_trait_t any_treat = {
	.free = any_free,
	.dump = any_dump,
	.type = any_type,
	.copy = any_copy,
	.move = any_move,
	.name = any_name
};



void     iter_shift_f(ax_iter_t* it, int i)
{
	it.point += i * ((ax_vector_t*)it->owner)->seq.elem_tr->size();
}

ax_ref_t iter_get_f(const ax_iter_t* it, int i)
{
	
}

void     iter_comp_f(const ax_iter_t* it1, const ax_iter_t* it2)
{

}

size_t   iter_dist_f(const ax_iter_t* it1, const ax_iter_t* it2)
{

}

void     iter_erase_f(ax_iter_t* it)
{

}

static size_t box_size(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	return vec->size;
}

static size_t box_maxsize(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	return vec->seq.tr->maxsize(any);
}

static ax_iter_t box_begin(ax_any_t* any)
{
	ax_iter_t it;
	it.owner = any;
}

static ax_iter_t box_end(ax_any_t* any)
{

}

static ax_iter_t box_rbegin(ax_any_t* any)
{

}

static ax_iter_t box_rend(ax_any_t* any)
{

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
	if (vec->size + 1 >= vec->capacity) {
		if(vec->capacity + 1 > vec->maxsize) {
			return ax_false;
		}
		vec->capacity += 100;
		if(vec->capacity > vec->maxsize)
			vec->capacity = vec->maxsize;
		vec->buffer = realloc(vec->buffer, vec->capacity);
	}
	vec->seq.elem_tr->copy(vec->buffer + vec->size, e);
	vec->size ++;
}

static ax_bool_t seq_pop(ax_any_t* any)
{
	ax_vector_t* vec = (ax_vector_t*)any;
	if (vec->size == 0)
		return ax_false;
	vec->size --;
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

ax_box_t* ax_vector_create(ax_vector_t* pt, ax_basic_type_t type, ax_basic_trait_t* elem_tr)
{
	if (pt == NULL) {
		ax_vector_t *vec = malloc(sizeof(ax_vector_t));
		pt->seq.box.any.flags = AX_AF_NEED_FREE;
	}

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
	pt->buffer = malloc(10 * pt->seq.elem_tr->size());
	pt->capacity = 10;
	pt->size = 0;

	return (ax_box_t*)pt;
}


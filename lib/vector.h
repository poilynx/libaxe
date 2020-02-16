#ifndef VECTOR_H_
#define VECTOR_H_
#include "def.h"
#include "seq.h"

struct ax_vector_st
{
	ax_seq_t seq;
	size_t size;
	size_t capacity;
	size_t maxsize;
	size_t elem_size;
	void* buffer;
};
typedef struct ax_vector_st ax_vector_t;

ax_any_t* ax_vector_create(ax_vector_t* pt, const ax_basic_trait_t* elem_tr);
#endif


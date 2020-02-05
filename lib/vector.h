#ifndef VECTOR_H_
#define VECTOR_H_
#include "base.h"
struct vector_st
{
	void* buffer;
	size_t size;
	size_t capacity;
	size_t elem_size;
}
typedef struct vector_st vector_t;

ax_box_t* ax_vector_make(ax_tuple_t* t);
#endif


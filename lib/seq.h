#ifndef SEQ_H_
#define SEQ_H_
#include "box.h"
#include "debug.h"
struct ax_seq_st;
typedef struct ax_seq_st ax_seq_t;

typedef void (*ax_seq_push_f)(ax_seq_t* box, void* e);
typedef void (*ax_seq_pop_f)(ax_seq_t* box);
typedef void (*ax_seq_sort_f)(ax_box_t* box);

struct ax_seq_trait_st
{
	ax_seq_push_f push;
	ax_seq_pop_f  pop;
	ax_seq_sort_f sort;
};
typedef struct ax_seq_trait_st ax_seq_trait_t;

struct ax_seq_st
{
	ax_box_t box;
	ax_seq_trait_t* tr;
};

#endif

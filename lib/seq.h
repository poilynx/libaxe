#ifndef SEQ_H_
#define SEQ_H_
#include "type.h"
#include "box.h"
#include "debug.h"
struct ax_basic_trait_st;
typedef struct ax_basic_trait_st ax_basic_trait_t;
struct ax_seq_st;
typedef struct ax_seq_st ax_seq_t;

typedef ax_bool_t(*ax_seq_push_f)(ax_any_t* any, void* e);
typedef ax_bool_t(*ax_seq_pop_f)(ax_any_t* any);
typedef void (*ax_seq_sort_f)(ax_any_t* any);

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
	const ax_seq_trait_t* tr;
	const ax_basic_trait_t* elem_tr;
};

#define ax_seq_push(_a, _e) (AX_TRAIT_FUN_PREFIX(ax_seq_push, (_a), AX_T_SEQ), ((ax_seq_t*)(_a))->tr->push(_a, (_e)))
#define ax_seq_pop(_a) (AX_TRAIT_FUN_PREFIX(ax_seq_pop, (_a), AX_T_SEQ), ((ax_seq_t*)(_a))->tr->pop(_a))
#define ax_seq_sort(_a) (AX_TRAIT_FUN_PREFIX(ax_seq_sort, (_a), AX_T_SEQ), ((ax_seq_t*)(_a))->tr->sort(_a))

#endif

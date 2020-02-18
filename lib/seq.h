#ifndef SEQ_H_
#define SEQ_H_
#include "type.h"
#include "box.h"
#include "debug.h"
struct ax_stuff_trait_st;
typedef struct ax_stuff_trait_st ax_stuff_trait_t;
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
	const ax_stuff_trait_t* elem_tr;
};

inline static ax_bool_t ax_seq_push(ax_any_t* a, void* e) { return ((ax_seq_t*)a)->tr->push(a, e); }
inline static ax_bool_t ax_seq_pop(ax_any_t* a)           { return ((ax_seq_t*)a)->tr->pop(a); }
inline static void ax_seq_sort(ax_any_t* a)          { ((ax_seq_t*)a)->tr->sort(a); }

#define ax_seq_push(_a, _e) (ax_ptrace(ax_seq_push), ax_seq_push((_a), (_e)))
#define ax_seq_pop(_a)      (ax_ptrace(ax_seq_pop), ax_seq_pop((_a)))
#define ax_seq_sort(_a)     (ax_ptrace(ax_seq_sort), ax_seq_sort((_a)))

#endif

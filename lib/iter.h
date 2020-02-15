#ifndef ITER_H_
#define ITER_H_
#include "debug.h"
#include "ref.h"
struct ax_iter_st;
typedef struct ax_iter_st ax_iter_t;

typedef void     (*ax_iter_shift_f)(ax_iter_t* it, int i);
typedef ax_ref_t (*ax_iter_get_f)(const ax_iter_t* it, int i);
typedef void     (*ax_iter_comp_f)(const ax_iter_t* it1, const ax_iter_t* it2);
typedef size_t   (*ax_iter_dist_f)(const ax_iter_t* it1, const ax_iter_t* it2);
typedef void     (*ax_iter_erase_f)(ax_iter_t* it);

struct ax_iter_trait_st
{
	ax_iter_shift_f shift;
	ax_iter_get_f  get;
	ax_iter_comp_f equal;
	ax_iter_comp_f less;
	ax_iter_dist_f dist;
	ax_iter_erase_f erase;
};
typedef struct ax_iter_trait_st ax_iter_trait_t;

struct ax_iter_st
{
	void* owner;
	void* point;
	ax_iter_trait_t* tr;
#ifndef NDEBUG
	uint32_t period;
#endif
};

#define ax_iter_shift(it, i)   (ax_ptrace(ax_iter_shift), it->tr->shift(it, i))
#define ax_iter_get(it)        (ax_ptrace(ax_iter_get),   it->tr->get(it, i))
#define ax_iter_equal(it1, it2)(ax_ptrace(ax_iter_equal), it->tr->equal(it1, it2))
#define ax_iter_less(it1, it2) (ax_ptrace(ax_iter_less),  it->tr->equal(it1, it2))
#define ax_iter_dist(it1, it2) (ax_ptrace(ax_iter_dist),  it->tr->dist(it1, it2))

#endif

#ifndef ITER_H_
#define ITER_H_
#include "debug.h"
#include "ref.h"
struct ax_iter_st;
typedef struct ax_iter_st ax_iter_t;

typedef void     (*ax_iter_shift_f)(ax_iter_t* it, int i);
typedef ax_ref_t (*ax_iter_get_f)(const ax_iter_t* it, int i);
typedef ax_bool_t(*ax_iter_comp_f)(const ax_iter_t* it1, const ax_iter_t* it2);
typedef size_t   (*ax_iter_dist_f)(const ax_iter_t* it1, const ax_iter_t* it2);
typedef ax_bool_t(*ax_iter_norm_f)(ax_iter_t* it);

struct ax_iter_trait_st
{
	ax_bool_t       norm;
	ax_iter_shift_f shift;
	ax_iter_get_f   get;
	ax_iter_comp_f  equal;
	ax_iter_comp_f  less;
	ax_iter_dist_f  dist;
};
typedef struct ax_iter_trait_st ax_iter_trait_t;

struct ax_iter_st
{
	void* owner;
	void* point;
	const ax_iter_trait_t* tr;
};

inline static ax_bool_t ax_iter_norm(ax_iter_t* it) { return it->tr->norm; }
inline static void ax_iter_shift(ax_iter_t* it, int i) { (it)->tr->shift((it), i); }
inline static ax_ref_t ax_iter_get(const ax_iter_t* it, int i) { return (it)->tr->get((it), i); }
inline static ax_bool_t ax_iter_equal(const ax_iter_t* it1, const ax_iter_t* it2) { return it1->tr->equal(it1, it2); }
inline static ax_bool_t ax_iter_less(const ax_iter_t* it1, const ax_iter_t* it2) { return it1->tr->equal(it1, it2); }
inline static size_t ax_iter_dist(const ax_iter_t* it1, const ax_iter_t* it2) { return it1->tr->dist(it1, it2); }

#define ax_iter_norm(it)       (ax_ptrace(ax_iter_norm),  ax_iter_norm(it))
#define ax_iter_shift(it, i)   (ax_ptrace(ax_iter_shift), ax_iter_shift((it), (i)))
#define ax_iter_get(it, i)     (ax_ptrace(ax_iter_get),   ax_iter_get(it, i))
#define ax_iter_equal(it1, it2)(ax_ptrace(ax_iter_equal), ax_iter_equal(it1, it2))
#define ax_iter_less(it1, it2) (ax_ptrace(ax_iter_less),  ax_iter_less(it1, it2))
#define ax_iter_dist(it1, it2) (ax_ptrace(ax_iter_dist),  ax_iter_dist(it1, it2))

#endif

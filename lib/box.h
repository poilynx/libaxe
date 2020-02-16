#ifndef BOX_H_
#define BOX_H_
#include "def.h"
#include "iter.h"
#include "ref.h"
#include "type.h"
#define AX_BT_SEQ 0
#define AX_BT_MAP 1
struct ax_box_st;
typedef struct ax_box_st ax_box_t;

typedef size_t   (*ax_box_size_f)(ax_any_t* any);
typedef ax_iter_t(*ax_box_iter_f)(ax_any_t* any);
typedef void     (*ax_box_erase_f) (ax_any_t* any, ax_iter_t* iter);

struct ax_box_trait_st
{
	ax_box_size_f size;
	ax_box_size_f maxsize;

	ax_box_iter_f begin;
	ax_box_iter_f end;
	ax_box_iter_f rbegin;
	ax_box_iter_f rend;

	ax_box_erase_f erase;
};
typedef struct ax_box_trait_st ax_box_trait_t;

struct ax_box_st
{
	ax_any_t any;
	const ax_box_trait_t* tr;
	char period;
};

static inline ax_iter_t ax_box_begin(ax_any_t* a) { return ((ax_box_t*)a)->tr->begin(a); }
static inline ax_iter_t ax_box_end(ax_any_t* a) { return ((ax_box_t*)a)->tr->end(a); }
static inline ax_iter_t ax_box_rbegin(ax_any_t* a) { return ((ax_box_t*)a)->tr->rbegin(a); }
static inline ax_iter_t ax_box_rend(ax_any_t* a) { return ((ax_box_t*)a)->tr->rend(a); }
static inline size_t    ax_box_size(ax_any_t* a) { return ((ax_box_t*)(a))->tr->size(a); }
static inline void      ax_box_erase(ax_any_t* a, ax_iter_t* it) { return ((ax_box_t*)(a))->tr->erase(a, it); }


#define ax_box_begin(_a)      (ax_ptrace(ax_box_begin), ax_box_begin((_a)))
#define ax_box_end(_a)        (ax_ptrace(ax_box_end), ax_box_end((_a)))
#define ax_box_rbegin(_a)     (ax_ptrace(ax_box_rbegin), ax_box_rbegin((_a)))
#define ax_box_rend(_a)       (ax_ptrace(ax_box_rend), ax_box_rend((_a)))
#define ax_box_size(_a)       (ax_ptrace(ax_box_size), ax_box_size((_a)))
#define ax_box_erase(_a, _it) (ax_ptrace(ax_box_erase), ax_box_erase((_a), (_it)))

#endif

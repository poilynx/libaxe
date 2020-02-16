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
typedef ax_iter_t(*ax_box_at_f)  (ax_any_t* any, void *index);
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

#define ax_box_begin(_a) (AX_TRAIT_FUN_PREFIX(ax_box_begin, (_a), AX_T_BOX), ((ax_box_t*)(_a))->tr->begin(_a))
#define ax_box_end(_a) (AX_TRAIT_FUN_PREFIX(ax_box_end, (_a), AX_T_BOX), ((ax_box_t*)(_a))->tr->end(_a))
#define ax_box_size(_a) (AX_TRAIT_FUN_PREFIX(ax_box_size, (_a), AX_T_BOX), ((ax_box_t*)(_a))->tr->size(_a))

#endif

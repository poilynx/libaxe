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

struct ax_box_trait_st
{
	ax_box_size_f size;
	ax_box_size_f maxsize;

	ax_box_iter_f begin;
	ax_box_iter_f end;
	ax_box_iter_f rbegin;
	ax_box_iter_f rend;
};
typedef struct ax_box_trait_st ax_box_trait_t;

struct ax_box_st
{
	ax_any_t any;
	ax_box_trait_t* tr;
	char sequel[0];
};

#endif

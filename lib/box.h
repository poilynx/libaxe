#ifndef BOX_H_
#define BOX_H_
#include "base.h"
#include "iter.h"
#include "ref.h"

#define AX_BT_SEQ 0
#define AX_BT_MAP 1
struct ax_box_st;
typedef struct ax_box_st ax_box_t;

typedef size_t   (*ax_box_size_f)(ax_box_t* box);
typedef ax_iter_t(*ax_box_iter_f)(ax_box_t* box);
typedef ax_iter_t(*ax_box_at_f)  (ax_box_t* box, void *index);
typedef char*    (*ax_box_dump_f)(ax_box_t* box, int indent);

struct ax_box_trait_st
{
	ax_box_size_f size;
	ax_box_size_f maxsize;

	ax_box_iter_f begin;
	ax_box_iter_f end;
	ax_box_iter_f rbegin;
	ax_box_iter_f rend;

	ax_box_dump_f dump;
};
typedef struct ax_box_trait_st ax_box_trait_t;

struct ax_box_st
{
#ifndef NDEBUG
	char type[4];
#endif
	ax_box_trait_t* tr;
	char sequel[0];
};

#endif

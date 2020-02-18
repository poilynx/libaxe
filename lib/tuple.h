#ifndef TUPLE_H_
#define TUPLE_H_
#include "stuff.h"
#define AX_TF_MUTABLE 0x01
struct ax_tuple_st;
typedef struct ax_tuple_st ax_tuple_t;
struct ax_vail_st;
typedef struct ax_vail_st ax_vail_t;
struct ax_tuple_item_st
{
	char type;
	char flag;
	size_t  count;
	void*   ptr;
};
typedef struct ax_tuple_item_st ax_tuple_item_t;

struct ax_tuple_st
{
	size_t size;
	ax_tuple_item_t* table;
	void* stash;
};
typedef struct ax_tuple_st ax_tuple_t;

ax_tuple_t* ax_tuple_make(ax_vail_t* vail);
void ax_tuple_free(ax_tuple_t* t);

#endif

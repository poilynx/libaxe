#ifndef VAIL_H_
#define VAIL_H_
#include "def.h"
#include "basic.h"
#include <stdint.h>
#include <stddef.h>
struct ax_vaf_item_st
{
	int8_t type;
	int8_t mut;
	uint8_t repeat;
	char label;
};
typedef struct ax_vaf_item_st ax_vaf_item_t;

struct ax_vaf_st
{
	char magic;
	char argc;
	ax_vaf_item_t table[0];
};
typedef struct ax_vaf_st ax_vaf_t;

struct ax_vail_node_st
{
	char mut;
	char type;
	char label;
	ax_basic_t value;
	size_t size;
	struct ax_vail_node_st* next;
};
typedef struct ax_vail_node_st ax_vail_node_t;

#define ax_vail_node_set(p, m, t, l, v, s) \
	((p)->mut = (m), \
	(p)->type = (t), \
	(p)->label = (l), \
	(p)->value = (v), \
	(p)->size = (s)) 


struct ax_vail_st
{
	size_t size;
	size_t capacity;
	struct ax_vail_node_st* head;
	struct ax_vail_node_st* tail;
};
typedef struct ax_vail_st ax_vail_t;

ax_vaf_t* ax_vaf_make(char *fmt);
void ax_vail_push(ax_vail_t* vail, ax_vail_node_t* node);
ax_vail_node_t* ax_vail_pop(ax_vail_t* vail);
ax_vail_t* ax_vail_read(ax_vaf_t* vaf, ...);

#endif

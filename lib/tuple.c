#include "tuple.h"
#include "vail.h"
#include "stuff.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

ax_tuple_t* ax_tuple_make(ax_vail_t* vail)
{
	ax_tuple_t* t = malloc(sizeof(ax_tuple_t));
	t->table = malloc(sizeof(ax_tuple_item_t) * vail->size);
	t->stash = malloc(vail->capacity);
	t->size = vail->size;

	void* stash_pos = t->stash;
	ax_vail_node_t* node = vail->head;
	size_t i;
	for (i=vail->size-1; node; node=node->next, i--) {
		t->table[i].ptr = stash_pos;
		t->table[i].type = node->type;
		if (node->mut) {
			t->table[i].flag = AX_TF_MUTABLE;
			t->table[i].count = node->size;
			memcpy(stash_pos, node->value.ptr, node->size);
			stash_pos += node->size;
		} else {
			t->table[i].flag = 0;
			t->table[i].count = 1;
			memcpy(stash_pos, &(node->value), node->size);
			stash_pos += node->size;
		}
	}
	return t;
}

void ax_tuple_free(ax_tuple_t* t)
{
	assert(t);
	free(t->table);
	free(t->stash);
	free(t);
}


#ifndef ITER_H_
#define ITER_H_

struct ax_box_st;
typedef struct ax_box_st ax_box_t;

typedef void node_t;

struct ax_iter_st
{
	struct ax_box_st* box;
	node_t* node;
};
typedef struct ax_iter_st ax_iter_t;

ax_iter_alloc(ax_box_t* box, node_t* node);

ax_ref_t ax_iter_get(ax_iter_t* iter, int i);

void ax_iter_forward(ax_iter_t* iter);
void ax_iter_back(ax_iter_t* iter);

void ax_iter_remove(ax_iter_t* iter)
#endif

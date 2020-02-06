#ifndef SEQ_H_
#define SEQ_H_

struct ax_box_st;
typedef struct ax_box_st ax_box_t;

typedef void    (*ax_seq_push_cb)  (ax_box_t* box, elem_t* elem);
typedef void    (*ax_seq_pop_cb)   (ax_box_t* box);
typedef void    (*ax_seq_sort)     (ax_box_t* box);

struct ax_seq_cbset_st
{
	ax_seq_push_cb push;
	ax_seq_pop_cb  pop;
	ax_seq_sort_cb sort;
};
typedef struct ax_seq_cbset_st ax_seq_cbset_t;

struct ax_seq_st
{
	ax_seq_cbset_t* cbset;
};
typedef struct ax_seq_st ax_seq_t;

void ax_seq_push(ax_box_t* box, ...);
void ax_seq_pop(ax_box_t* box);
ax_ref_t ax_seq_front(ax_box_t* box);
ax_ref_t ax_seq_back(ax_box_t* box);
void ax_seq_pour(ax_box_t* box, void* buf);
#endif

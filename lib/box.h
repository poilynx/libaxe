#ifndef BOX_H_
#define BOX_H_
#include "base.h"
#include "iter.h"
#include "ref.h"


/* For Finding elements and their attributes */
typedef void node_t;
/* Element raw data */
typedef void elem_t;

#define AX_BT_SEQ 0
#define AX_BT_MAP 1

typedef size_t  (*ax_box_size_cb)  (ax_box_t* box);
typedef node_t* (*ax_box_end_cb)   (ax_box_t* box);
/* overflow if true returned */
typedef ax_bool_t(*ax_box_shift_cb)(ax_box_t* box, node_t** n, uint64 l);
typedef uint64_t(*ax_box_distance_cb)(ax_box_t* box, node_t* n);
typedef node_t* (*ax_box_locate_cb)(ax_box_t* box, void *index);
typedef node_t* (*ax_box_remove_cb)(ax_box_t* box, node_t*);
typedef elem_t* (*ax_box_value_cb) (ax_box_t* box, node_t* n);
typedef char*   (*ax_box_dump_cb)  (ax_box_t* box, size_t indent);

typedef void    (*ax_elem_clean_cb)(const elem_t* e);
typedef uint32_t(*ax_elem_hash_cb) (const elem_t* e);
typedef ax_bool (*ax_elem_equal_cb)(const elem_t* e1, const elem_t* e2);
typedef ax_bool (*ax_elem_less_cb) (const elem_t* e1, const elem_t* e2);
typedef char*   (*ax_elem_tostr_cb)(const elem_t* e);
typedef void    (*ax_elem_copy_cb) (elem_t* dst, elem_t* src);

struct ax_box_cbset_st
{
	ax_box_size_cb     size;
	ax_box_size_cb     maxsize;
	ax_box_end_cb      begin;
	ax_box_end_cb      end;
	ax_box_shift_cb    shift;
	ax_box_distance_cb distance;
	ax_box_value_cb    value;
	ax_box_dump_cb     dump;
};
typedef struct ax_box_cbset_st ax_box_cbset_t;

/* entity? */
struct ax_elem_cbset_st
{
	ax_elem_clean_cb clean; 
	ax_elem_hash_cb  hash;
	ax_elem_equal_cb equal;
	ax_elem_less_cb  less;
	ax_elem_tostr_cb tostr;
	ax_elem_copy_cb  copy;
};
typedef struct ax_elem_cbset_st ax_elem_cbset_t;

struct ax_box_st
{
	char box_type;
	char elem_type;
	char idx_type;
	ax_box_cbset_t* box_cbset;
	ax_elem_cbset_t* elem_cbset;
	union {
		ax_seq_cbset_t *seq_cbset;
	}
	char header[0];
};
typedef struct ax_box_st ax_box_t;

size_t    ax_box_maxsize(ax_box_t* box);
size_t    ax_box_size(ax_box_t* box);
ax_iter_t ax_box_begin(ax_box_t* box);
ax_iter_t ax_box_end(ax_box_t* box);
ax_ref_t  ax_box_at(ax_box_t* box, ...);
ax_bool_t ax_box_empty(ax_box_t* box);
void      ax_box_clear(ax_box_t* box);
ax_box_t* ax_box_clone(ax_box_t* box);
int       ax_box_merge(ax_box_t* dst, ax_box_t* src);
void      ax_box_dump(ax_box_t* box);

#endif

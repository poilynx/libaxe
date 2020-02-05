#ifndef BOXI_H_
#define BOXI_H_
static size_t box_size_cb(ax_box_t* box);
static node_t* box_end_cb(ax_box_t* box);
static node_t* box_shift_cb(ax_box_t* box, node_t* n, uint64 l);
static uint64_t box_distance_cb(ax_box_t* box, node_t* n);
static node_t* box_locate_cb(ax_box_t* box, void* index);
static elem_t* box_value_cb(ax_box_t* box, node_t* n);
static char* box_dump_cb(ax_box_t* box);

static void elem_clean_cb(const elem_t* e);
static uint32_t elem_hash_cb(const elem_t* e);
static ax_bool elem_equal_cb(const elem_t* e1, const elem_t* e2);
static ax_bool elem_less_cb(const elem_t* e1, const elem_t* e2);
static char* elem_tostr_cb(const elem_t* e);
static void elem_copy_cb(elem_t* dst, elem_t* src);

#endif

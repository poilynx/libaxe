#include "box.h"
#include "ref.h"
#include <stdio.h>
#include <stdarg.h>


size_t ax_box_maxsize(ax_box_t* box)
{
	return box->box_cbset->maxsize(box);
}

size_t ax_box_size(ax_box_t* box)
{
	return box->box_cbset.size(box);
}

ax_iter_t ax_box_begin(ax_box_t* box)
{
	ax_iter_t iter;
	iter.box = box;
	iter.node = box->box_cbset.begin(box);
	return iter;
}

ax_iter_t ax_box_end(ax_box_t* box)
{
	ax_iter_t iter;
	iter.box = box;
	iter.node = box->box_cbset.end(box);
	return iter;
}

ax_ref_t ax_box_at(ax_box_t* box, ...)
{
	va_list va;
	va_start(va, box);
	va_end(va);
	ax_basic_t basic;
	ax_basic_vcopy(box->idx_type, &basic, va);
	return box->boxcb.locate(box, &clip);
}

ax_bool_t ax_box_empty(ax_box_t* box)
{
	return box->box_cbset.size(box) == 0;
}

void ax_box_clear(ax_box_t* box)
{
	node_t* node = box->box_cbset.begin(box);
	while(node) {
		elem_t* elem = box->box_cbset.value(box, node);
		box->elem_cbset.clean(elem);
		node = box->box_cbset.remove(box, node);
	}
}

ax_box_t* ax_box_clone(ax_box_t* box)
{
	//can not impl
}

int ax_box_merge(ax_box_t* dst, ax_box_t* src)
{
	//can not impl
}

void ax_box_dump(ax_box_t* box)
{
	box->box_cbset.dump(box, 0);
}





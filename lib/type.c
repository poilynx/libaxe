#include "type.h"
#include "stuff.h"
#include <stdio.h>
#include <stdlib.h>

ax_bool_t ax_IS(ax_any_t* any, char type)
{
	switch(any->tr->type) {
		case AX_T_ANY:
			switch(type) {
				case AX_T_ANY: break;
				default: return ax_false;
			}
		case AX_T_BOX: 
			switch(type) {
				case AX_T_ANY:
				case AX_T_BOX: break;
				default: return ax_false;
			}
		case AX_T_MAP:
			switch(type) {
				case AX_T_ANY:
				case AX_T_BOX:
				case AX_T_MAP: break;
				default: return ax_false;
			}
		case AX_T_SEQ:
			switch(type) {
				case AX_T_ANY:
				case AX_T_BOX:
				case AX_T_SEQ: break;
				default: return ax_false;
			}
	}
	return ax_true;

}

const char* ax_type_name(char type)
{
	switch(type) {
		case AX_T_ANY: return "any";
		case AX_T_BOX: return "any_box";
		case AX_T_SEQ: return "any_box_seq";
		case AX_T_MAP: return "any_box_map";
		default: return "unknow";
	}
}

static ax_bool_t stuff_equal(const void* e1, const void* e2)
{
	return (void*)e1 == (void*)e2;
}

static ax_bool_t stuff_less(const void* e1, const void* e2)
{
	return(void*)e1 < (void*)e2;
}

static void stuff_free(const void* e)
{
	ax_any_t* any = (ax_any_t*)e;
	any->tr->free(any);
}

static size_t stuff_hash(const void* e)
{
	return (size_t)*(void**)e;
}

static char* stuff_text(const void* e)
{
	char*buf = malloc(20);
	sprintf(buf, "0x%lX", *(long unsigned int*)e);
	return buf;
}

static void stuff_copy(void* dst, const void* src)
{
	ax_any_t* anys = *(ax_any_t**)src;
	*(void**)dst = anys->tr->copy(src);
}

static ax_stuff_trait_t any_stuff_trait = {
	.equal = stuff_equal,
	.less = stuff_less,
	.hash = stuff_hash,
	.free = stuff_free,
	.copy = stuff_copy,
	.text = stuff_text 
};

ax_stuff_trait_t* ax_any_stuff_trait()
{
	return &any_stuff_trait;
}

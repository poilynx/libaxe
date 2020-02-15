#include "type.h"
#include "basic.h"
#include <stdio.h>
#include <stdlib.h>

ax_bool_t ax_IS(ax_any_t* any, char type)
{
	switch(any->tr->type(any)) {
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

static ax_bool_t basic_equal(const void* e1, const void* e2)
{
	return (void*)e1 == (void*)e2;
}

static ax_bool_t basic_less(const void* e1, const void* e2)
{
	return(void*)e1 < (void*)e2;
}

static void basic_free(const void* e)
{
	ax_any_t* any = (ax_any_t*)e;
	any->tr->free(any);
}

static size_t basic_hash(const void* e)
{
	return (size_t)*(void**)e;
}

static char* basic_tostr(const void* e)
{
	char*buf = malloc(20);
	sprintf(buf, "0x%X", *(void**)e);
	return buf;
}

static void basic_copy(void* dst, const void* src)
{
	ax_any_t* anys = *(ax_any_t**)src;
	*(void**)dst = anys->tr->copy(src);
}

static ax_basic_trait_t any_basic_trait = {
	.equal = basic_equal,
	.less = basic_less,
	.hash = basic_hash,
	.free = basic_free,
	.copy = basic_copy,
	.tostr = basic_tostr
};

ax_basic_trait_t* ax_any_basic_trait()
{
	return &any_basic_trait;
}

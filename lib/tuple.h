#ifndef TUPLE_H_
#define TUPLE_H_
#include "basic.h"
// i8 i16 i32 i64 u8 u16 u32 u64 f lf llf p s r
// hhd hd d lld hhu hu u llu f lf llf p s r
// i8*3, i8[3], B
// ax_tuple_alloc("i8x3_i32[2]_r", 1, 2, 3, &arr, buf, sizeof(buf)); 

//static char sigma(char c) {
//	
//	switch(c) {
//		case '0':
//		case '1':
//		break;
//	}
//}
#define AX_TF_MUTABLE 0x01
struct ax_tuple_item_st
{
	ax_basic_type_t type;
	uint8_t flag;
	char    label;
	size_t  count;
	void* ptr;
};
typedef struct ax_tuple_item_st ax_tuple_item_t;

struct ax_tuple_st
{
	size_t size;
	ax_tuple_item_t* item_tab;
	void* stash;
};
typedef struct ax_tuple_st ax_tuple_t;

ax_tuple_t* ax_tuple_alloc(char* layout, ...);

#endif

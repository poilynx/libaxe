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

struct ax_tuple_st
{
	size_t tuple_size;
	ax_basic_type_t* item_ptr_tab;
	size_t* item_size_tab;
	void* stash;
};
typedef struct ax_tuple_st ax_tuple_t;

ax_tuple_t* ax_tuple_alloc(char* layout, ...);



#endif

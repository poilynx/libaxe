#ifndef TUPLE_H_
#define TUPLE_H_
#include "basic.h"
// i8 i16 i32 i64 u8 u16 u32 u64 f lf llf p s r
// hhd hd d lld hhu hu u llu f lf llf p s r
// i8*3, i8[3], B
struct ax_tuple_st
{
	size_t size;
	void* term_tab;
	ax_basic_type_t* type_tab;

}
typedef struct ax_tuple_st ax_tuple_t;

ax_tuple_t* ax_tuple_alloc(char* layout);



#endif

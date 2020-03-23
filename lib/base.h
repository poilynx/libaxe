#ifndef BASE_H_
#define BASE_H_
#include <stddef.h>
typedef void*(*ax_malloc_f)(size_t size);
typedef void(*ax_free_f)(void* p);
//allocator
struct ax_base_st
{
	ax_malloc_f malloc;
	ax_free_f   free;
};
typedef struct ax_base_st ax_base;
#endif


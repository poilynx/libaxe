#ifndef BASE_H_
#define BASE_H_
#include <stdint.h>

typedef enum {
	ax_0, ax_1, ax_2, ax_3, ax_4,
	ax_5, ax_6, ax_7, ax_8, ax_9,
	ax_10, ax_11, ax_12, ax_13, ax_14,
	ax_15, ax_16
} ax_argc_t;


//struct ax_box_st;
//typedef struct ax_box_st * ax_box_t;

typedef enum { ax_false, ax_true } ax_bool_t;


void __ax_fault(const char*, int, const char*, const char*, const char*, ...);

#undef ax_assert
#ifdef NDEBUG
# define ax_assert(__e, __f) ((void)0)
#else
//void __ax_assert_fail(const char*, int, const char*, const char*, ...);
# define ax_assert(__e, __f ...) \
	((__e) ? (void)0 : __ax_fault(__FILE__, __LINE__, __FUNCTION__, "Assertion failed", __f))
#endif

#undef ax_fault
#define ax_fault(__f ...)  (__ax_fault(__FILE__, __LINE__, __FUNCTION__, "Fault", __f))

#endif

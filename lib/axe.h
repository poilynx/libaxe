#ifndef AXE_H_
#define AXE_H_
#include "def.h"
#include "iter.h"
#include "box.h"
void ax__init(ax_bool_t debug, ax_bool_t trace);
void ax__uninit();

#ifdef AX_TRACE
# define AX__TRACE_ENABLE 1
#else
# define AX__TRACE_ENABLE 0
#endif

#ifdef AX_DEBUG
# define AX__DEBUG_ENABLE 1
#else
# define AX__DEBUG_ENABLE 0
#endif

#define ax_init() ax__init(AX__DEBUG_ENABLE, AX__TRACE_ENABLE)
#define ax_uninit() ax__uninit()

#define ax_foreach(_r, _a) \
	for ( char __for_flag = 1 ; __for_flag ; ) \
	for ( ax_ref_t _r ; __for_flag ; __for_flag = 0) \
	for ( \
		ax_iter_t _it = ax_box_begin((_a)), __##_it##_end = ax_box_end((_a)); \
		!ax_iter_equal(&(_it), &(__##_it##_end)) && ((_r) = ax_iter_get(&_it, 0), 1); \
		ax_iter_shift(&_it, 1) \
	)

#endif

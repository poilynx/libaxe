#ifndef AXE_H_
#define AXE_H_
#include "def.h"
void ax__init(ax_bool_t debug, ax_bool_t trace);
void ax__uninit();
#ifdef AX_TRACE
# define __TRACE_ENABLE 1
#else
# define __TRACE_ENABLE 0
#endif

#ifdef AX_DEBUG
# define __DEBUG_ENABLE 1
#else
# define __DEBUG_ENABLE 0
#endif

#define ax_init() ax__init(__DEBUG_ENABLE, __TRACE_ENABLE)
#define ax_uninit() ax__uninit()

#undef __TRACE_ENABLE
#undef __DEBUG_ENABLE

#endif

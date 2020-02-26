#ifndef AXE_H_
#define AXE_H_

void ax__init(int trace);
#ifdef AX_TRACE
# define ax_init() ax__init(1)
#else
# define ax_init() ax__init(0)
#endif

#endif

#ifndef DEBUG_H_
#define DEBUG_H_
void ax__ptrace(const char*, const char*, int, const char*);
void ax__fault(const char*, const char*, int, const char*, const char*, ...);

#undef ax_assert
#ifdef AX_NO_DEBUG
# define ax_assert(__e, __f) ((void)0)
#else
# define ax_assert(__e, __f, ...) ((__e) \
	? (void)0 : ax__fault(__FILE__, __FUNCTION__, __LINE__, "assertion failed", __f, ##__VA_ARGS__))
#endif

#undef ax_ptrace
#ifndef AX_TRACE
# define ax_ptrace(__c) ((void)0)
#else
# define ax_ptrace(__c) ax__ptrace(__FILE__, __FUNCTION__, __LINE__, #__c)
#endif

#undef ax_fault
#define ax_fault(__f, ...) (ax__fault(__FILE__,  __FUNCTION__,__LINE__, "error", __f, ##__VA_ARGS__))

#endif

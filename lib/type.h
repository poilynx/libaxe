#ifndef TYPE_H_
#define TYPE_H_
#include "def.h"

#define AX_T_ANY 0
#define AX_T_BOX 1
#define AX_T_MAP 2
#define AX_T_SEQ 3

struct ax_any_st;
typedef struct ax_any_st ax_any_t;
struct ax_basic_trait_st;
typedef struct ax_basic_trait_st ax_basic_trait_t;

typedef void (*ax_free_f)  (ax_any_t* any);
typedef void (*ax_dump_f)  (const ax_any_t* any, int ind);
typedef char (*ax_type_f)  (const ax_any_t* any);
typedef ax_any_t*(*ax_copy_f)  (const ax_any_t* any);
typedef ax_any_t*(*ax_move_f)  (ax_any_t* any);
typedef char*(*ax_name_f)  (const ax_any_t* any);

struct ax_any_trait_st
{
	ax_free_f   free;
	ax_dump_f   dump;
	ax_type_f   type;
	ax_copy_f   copy;
	ax_move_f   move;
	ax_name_f   name;
};
typedef struct ax_any_trait_st ax_any_trait_t;

#define AX_AF_NEED_FREE 0x01
#define AX_AF_FREED     0x02
struct ax_any_st
{
	char magic[3];
	char flags;
	const ax_any_trait_t* tr;
};

ax_bool_t ax_IS(ax_any_t* any, char type);
const char* ax_type_name(char type);
ax_basic_trait_t* ax_any_basic_trait();

#ifndef AX_NO_ASSERT
inline static ax_bool_t ax__is_any(ax_any_t* any) {
	return any->magic[0] == 'A'
		&& any->magic[1] == 'X'
		&& any->magic[2] == '\0';
}
#endif

static inline void ax_free(ax_any_t *a) { a->tr->free(a); }
static inline char ax_type(ax_any_t *a) { return a->tr->type(a); }
static inline ax_any_t* ax_move(ax_any_t *a) { return a->tr->move(a); }
static inline ax_any_t* ax_copy(ax_any_t *a) { return a->tr->copy(a); }
static inline char* ax_name(ax_any_t *a) { return a->tr->name(a); }

#define ax_free(_a)  (ax_ptrace(ax_free), ax_free(_a))
#define ax_type(_a)  (ax_ptrace(ax_type), ax_type(_a))
#define ax_move(_a)  (ax_ptrace(ax_move), ax_move(_a))
#define ax_copy(_a)  (ax_ptrace(ax_copy), ax_copy(_a))
#define ax_name(_a)  (ax_ptrace(ax_name), ax_name(_a))

#endif

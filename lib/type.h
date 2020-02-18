#ifndef TYPE_H_
#define TYPE_H_
#include "def.h"

#define AX_T_ANY 0
#define AX_T_BOX 1
#define AX_T_MAP 2
#define AX_T_SEQ 3

struct ax_any_st;
typedef struct ax_any_st ax_any_t;
struct ax_stuff_trait_st;
typedef struct ax_stuff_trait_st ax_stuff_trait_t;

typedef void (*ax_free_f)  (ax_any_t* any);
typedef void (*ax_dump_f)  (const ax_any_t* any, int ind);
typedef ax_any_t*(*ax_copy_f)  (const ax_any_t* any);
typedef ax_any_t*(*ax_move_f)  (ax_any_t* any);

struct ax_any_trait_st
{
	const char* name;
	const char  type;
	ax_free_f   free;
	ax_dump_f   dump;
	ax_copy_f   copy;
	ax_move_f   move;
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
ax_stuff_trait_t* ax_any_stuff_trait();

inline static ax_bool_t ax_is_any(ax_any_t* any) {
	return any->magic[0] == 'A'
		&& any->magic[1] == 'X'
		&& any->magic[2] == '\0';
}

static inline void      ax_any_free(ax_any_t *a) { a->tr->free(a); }
static inline char      ax_any_type(ax_any_t *a) { return a->tr->type; }
static inline ax_any_t* ax_any_move(ax_any_t *a) { return a->tr->move(a); }
static inline ax_any_t* ax_any_copy(ax_any_t *a) { return a->tr->copy(a); }
static inline const char* ax_any_name(ax_any_t *a) { return a->tr->name; }

#define ax_any_free(_a) (ax_ptrace(ax_any_free), ax_any_free(_a))
#define ax_any_type(_a) (ax_ptrace(ax_any_type), ax_any_type(_a))
#define ax_any_move(_a) (ax_ptrace(ax_any_move), ax_any_move(_a))
#define ax_any_copy(_a) (ax_ptrace(ax_any_copy), ax_any_copy(_a))
#define ax_any_name(_a) (ax_ptrace(ax_any_name), ax_any_name(_a))

#endif

#ifndef TYPE_H_
#define TYPE_H_

#define AX_TN_ANY "any"
#define AX_TN_BOX "box"
#define AX_TN_MAP "map"
#define AX_TN_SEQ "seq"
typedef void(*ax_free_f)(ax_t* any);
typedef ax_t*(*ax_clone_f)(ax_t* any);
typedef void(*ax_dump_f)(ax_t* any);
typedef char*(*ax_typeof_f)(ax_t* any);
typedef char*(*ax_name_f)(ax_t* any);
typedef ax_bool_t(*ax_is_f)(ax_t* any, const char* nm);

struct ax_trait_st
{
	ax_free_f   free;
	ax_clone_f  clone;
	ax_dump_f   dump;
	ax_typeof_f typeof;
	ax_name_f   name;
	ax_is_f     is;
}
typedef struct ax_trait_st ax_trait_t;
struct ax_st
{
	ax_trait_t* tr;
	char flags;
#ifndef NDEBUG
	char magic[2];
#endif
}
typedef struct ax_st ax_t;

void ax__check_type(ax_t* any, const char* nm);

#endif

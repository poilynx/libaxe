/*
 * Copyright (c) 2020 Li hsilin <lihsilyn@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef ANY_H_
#define ANY_H_
#include "def.h"
#include "debug.h"

#define AX_T_ANY 0
#define AX_T_TUP 1
#define AX_T_BOX 2
#define AX_T_MAP 3
#define AX_T_SEQ 4
#define AX_T_STR 5

struct ax_any_st;
typedef struct ax_any_st ax_any;

struct ax_stuff_trait_st;
typedef struct ax_stuff_trait_st ax_stuff_trait;

typedef ax_any ax_abox;
typedef ax_any ax_aseq;
typedef ax_any ax_astr;
typedef ax_any ax_amap;

typedef void   (*ax_free_f)  (      ax_any* this);
typedef void   (*ax_dump_f)  (const ax_any* this, int ind);
typedef ax_any*(*ax_copy_f)  (const ax_any* this);
typedef ax_any*(*ax_move_f)  (      ax_any* this);

struct ax_any_trait_st
{
	const char* name;
	const char  type;
	ax_free_f   free;
	ax_dump_f   dump;
	ax_copy_f   copy;
	ax_move_f   move;
};
typedef struct ax_any_trait_st ax_any_trait;

#define AX_AF_FREED   0x01
#define AX_AF_RENTED  0x02
#define AX_AF_CONST   0x04
struct ax_any_st
{
#ifdef AX_DEBUG
	char magic[4];
#endif
	int flags;
	const ax_any_trait* tr;
};

bool ax_IS(const ax_any* any, char type);
const char* ax_type_name(char type);
ax_stuff_trait* ax_any_stuff_trait();

static inline const char* ax_any_name (const ax_any* this) { return this->tr->name; }
static inline char        ax_any_type (const ax_any* this) { return this->tr->type; }
static inline void        ax_any_free (      ax_any* this) { return this->tr->free(this); }
static inline ax_any*     ax_any_copy (const ax_any* this) { return this->tr->copy(this); }
static inline ax_any*     ax_any_move (      ax_any* this) { return this->tr->move(this); }

#define ax_any_name(this) (ax_step(ax_any_name), ax_any_name(this))
#define ax_any_type(this) (ax_step(ax_any_type), ax_any_type(this))
#define ax_any_free(this) (ax_step(ax_any_free), ax_any_free(this))
#define ax_any_copy(this) (ax_step(ax_any_copy), ax_any_copy(this))
#define ax_any_move(this) (ax_step(ax_any_move), ax_any_move(this))

#ifdef AX_DEBUG
inline static void ax_any_set_magic(const ax_any* any)
{
	/*
	char *p = any->magic;
	*p++ = 'A';
	*p++ = 'B';
	*p++ = 'C';
	*p   = 'D';
	*/
	*(uint32_t*)any->magic = *(uint32_t*)"AXE";
}

inline static bool ax_any_check_magic(const ax_any* any)
{
	/*
	return any->magic[0] == 'A'
		&& any->magic[1] == 'X'
		&& any->magic[2] == 'E'
		&& any->magic[3] == '\0';
		*/
	return *(uint32_t*)any->magic == *(uint32_t*)"AXE";
}

inline static void ax_any_assert_type(const ax_any* any, char type)
{
	ax_panic_if(!ax_any_check_magic(any), AX_LM_ERROR, "Invalid !any pointer");
	ax_panic_if(!ax_IS((ax_any*)any, type), AX_LM_ERROR, "Not a %s, but %s", ax_type_name(type), ax_any_name((ax_any*)any));
}
#endif

#endif

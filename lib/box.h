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

#ifndef BOX_H_
#define BOX_H_
#include "def.h"
#include "iter.h"
#include "ref.h"
#include "any.h"
#define AX_BT_SEQ 0
#define AX_BT_MAP 1
struct ax_box_st;
typedef struct ax_box_st ax_box;

typedef size_t   (*ax_box_size_f)(ax_any* any);
typedef ax_iter(*ax_box_iter_f)(ax_any* any);
typedef ax_iter(*ax_box_erase_f) (ax_any* any, ax_iter* iter);
typedef void     (*ax_box_clear_f)(ax_any* any);


struct ax_box_trait_st
{
	ax_box_size_f size;
	ax_box_size_f maxsize;

	ax_box_iter_f begin;
	ax_box_iter_f end;
	ax_box_iter_f rbegin;
	ax_box_iter_f rend;

	ax_box_clear_f clear;
	ax_box_erase_f erase;
};
typedef struct ax_box_trait_st ax_box_trait;

struct ax_box_st
{
	ax_any any;
	const ax_box_trait* tr;
};

static inline ax_iter ax_box_begin (ax_any* a)  { return ((ax_box*)a)->tr->begin(a); }
static inline ax_iter ax_box_end   (ax_any* a)  { return ((ax_box*)a)->tr->end(a); }
static inline ax_iter ax_box_rbegin(ax_any* a)  { return ((ax_box*)a)->tr->rbegin(a); }
static inline ax_iter ax_box_rend  (ax_any* a)  { return ((ax_box*)a)->tr->rend(a); }
static inline size_t  ax_box_size  (ax_any* a)  { return ((ax_box*)(a))->tr->size(a); }
static inline void    ax_box_clear (ax_any* a)  { ((ax_box*)(a))->tr->clear(a); }
static inline ax_iter ax_box_erase (ax_any* a, ax_iter* it) { return ((ax_box*)(a))->tr->erase(a, it); }


#define ax_box_begin(_a)      (ax_step(ax_box_begin), ax_box_begin((_a)))
#define ax_box_end(_a)        (ax_step(ax_box_end), ax_box_end((_a)))
#define ax_box_rbegin(_a)     (ax_step(ax_box_rbegin), ax_box_rbegin((_a)))
#define ax_box_rend(_a)       (ax_step(ax_box_rend), ax_box_rend((_a)))
#define ax_box_size(_a)       (ax_step(ax_box_size), ax_box_size((_a)))
#define ax_box_clear(_a)      (ax_step(ax_box_clear), ax_box_clear((_a)))
#define ax_box_erase(_a, _it) (ax_step(ax_box_erase), ax_box_erase((_a), (_it)))

#endif

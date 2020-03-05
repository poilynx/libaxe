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

typedef size_t  (*ax_box_size_f)  (const ax_abox* this);
typedef ax_iter (*ax_box_iter_f)  (const ax_abox* this);
typedef ax_iter (*ax_box_erase_f) (      ax_abox* this, ax_iter* iter);
typedef void    (*ax_box_clear_f) (      ax_abox* this);


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

static inline ax_iter ax_box_begin (const ax_abox* this)  { return ((ax_box*)(this))->tr->begin(this); }
static inline ax_iter ax_box_end   (const ax_abox* this)  { return ((ax_box*)(this))->tr->end(this); }
static inline ax_iter ax_box_rbegin(const ax_abox* this)  { return ((ax_box*)(this))->tr->rbegin(this); }
static inline ax_iter ax_box_rend  (const ax_abox* this)  { return ((ax_box*)(this))->tr->rend(this); }
static inline size_t  ax_box_size  (const ax_abox* this)  { return ((ax_box*)(this))->tr->size(this); }
static inline void    ax_box_clear (      ax_abox* this)  { ((ax_box*)(this))->tr->clear(this); }
static inline ax_iter ax_box_erase (      ax_abox* this, ax_iter* it) { return ((ax_box*)(this))->tr->erase(this, it); }

#define ax_box_begin(this)      (ax_step(ax_box_begin),  ax_box_begin((this)))
#define ax_box_end(this)        (ax_step(ax_box_end),    ax_box_end((this)))
#define ax_box_rbegin(this)     (ax_step(ax_box_rbegin), ax_box_rbegin((this)))
#define ax_box_rend(this)       (ax_step(ax_box_rend),   ax_box_rend((this)))
#define ax_box_size(this)       (ax_step(ax_box_size),   ax_box_size((this)))
#define ax_box_clear(this)      (ax_step(ax_box_clear),  ax_box_clear((this)))
#define ax_box_erase(this, _it) (ax_step(ax_box_erase),  ax_box_erase((this), (_it)))

#endif

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

#ifndef SEQ_H_
#define SEQ_H_
#include "any.h"
#include "box.h"
#include "debug.h"
struct ax_stuff_trait_st;
typedef struct ax_stuff_trait_st ax_stuff_trait;
struct ax_seq_st;
typedef struct ax_seq_st ax_seq;
struct ax_seq_trait_st;
typedef struct ax_seq_trait_st ax_seq_trait;

typedef ax_pseq (*ax_seq_alloc_f)  (ax_seq_trait* seq_tr, ax_stuff_trait* elem_tr);
typedef bool    (*ax_seq_push_f)   (ax_pseq this, ax_cref elem);
typedef ax_iter (*ax_seq_find_f)   (ax_pseq this, ax_cref elem);
typedef bool    (*ax_seq_pop_f)    (ax_pseq this);
typedef void    (*ax_seq_sort_f)   (ax_pseq this);
typedef void    (*ax_seq_invert_f) (ax_pseq this);

struct ax_seq_trait_st
{
	ax_seq_alloc_f alloc;
	ax_seq_push_f push;
	ax_seq_pop_f  pop;
	ax_seq_sort_f sort;
	ax_seq_find_f find;
	ax_seq_invert_f invert;
};

struct ax_seq_st
{
	ax_box box;
	const ax_seq_trait* tr;
	const ax_stuff_trait* elem_tr;
};

inline static ax_pseq ax_seq_alloc  (ax_seq_trait* seq_tr, ax_stuff_trait* elem_tr) { return seq_tr->alloc(seq_tr, elem_tr);}

inline static bool    ax_seq_push   (ax_pseq this, ax_cref elem) { return ((ax_seq*)this)->tr->push(this, elem); }
inline static ax_iter ax_seq_find   (ax_pseq this, ax_cref elem) { return ((ax_seq*)this)->tr->find(this, elem); }
inline static bool    ax_seq_pop    (ax_pseq this)               { return ((ax_seq*)this)->tr->pop(this); }
inline static void    ax_seq_sort   (ax_pseq this)               { return ((ax_seq*)this)->tr->sort(this); }
inline static void    ax_seq_invert (ax_pseq this)               { return ((ax_seq*)this)->tr->invert(this); }

#define ax_seq_push(this, _e) (ax_step(ax_seq_push), ax_seq_push((this), (_e)))
#define ax_seq_pop(this)      (ax_step(ax_seq_pop),  ax_seq_pop((this)))
#define ax_seq_sort(this)     (ax_step(ax_seq_sort), ax_seq_sort((this)))
#define ax_seq_find(this)     (ax_step(ax_seq_find), ax_seq_find((this)))
#define ax_seq_invert(this)   (ax_step(ax_seq_sort), ax_seq_invert((this)))

#endif

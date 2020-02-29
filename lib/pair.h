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

#ifndef PAIR_H_
#define PAIR_H_
#include "stuff.h"
#include "ref.h"
struct ax_pair_st {};
typedef struct ax_pair_st ax_pair_t;

typedef ax_ref_t(*ax_pair_field_f)(ax_pair_t* pair);
struct ax_pair_trait_st
{
	ax_pair_field_f key;
	ax_pair_field_f value;
};
typedef struct ax_pair_trait_st ax_pair_trait_t;


inline static ax_pair_t* ax_rget_pair(ax_ref_t r) { ax_ref_check(r, ax_stuff_pwl('P')); return r.ptr; }
inline static ax_ref_t ax_rset_pair(ax_pair_t*  p) { return ax_ref_make(p, ax_stuff_pwl('P')); }

#define ax_rget_pair(_r)  (ax_step(ax_rset_pair), ax_rget_pair((_r)))
#define ax_rset_pair(_p) (ax_step(ax_rset_pair), ax_rset_pair((_p))) 

#endif

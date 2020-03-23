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

#ifndef ITER_H_
#define ITER_H_
#include "debug.h"
#include "ref.h"
struct ax_iter_st;
typedef struct ax_iter_st ax_iter;

typedef void   (*ax_iter_shift_f)(ax_iter* it, int i);
typedef ax_ref (*ax_iter_get_f)  (const ax_iter* it, int i);
typedef bool   (*ax_iter_comp_f) (const ax_iter* it1, const ax_iter* it2);
typedef size_t (*ax_iter_dist_f) (const ax_iter* it1, const ax_iter* it2);
typedef bool   (*ax_iter_norm_f) (ax_iter* it);

struct ax_iter_trait_st
{
	bool       norm;
	ax_iter_shift_f shift;
	ax_iter_get_f   get;
	ax_iter_comp_f  equal;
	ax_iter_comp_f  less;
	ax_iter_dist_f  dist;
};
typedef struct ax_iter_trait_st ax_iter_trait;

struct ax_iter_st
{
	const void* owner;
	void* point;
	const ax_iter_trait* tr;
};

inline static bool   ax_iter_norm (ax_iter* it) { return it->tr->norm; }
inline static void   ax_iter_shift(ax_iter* it, int i) { (it)->tr->shift((it), i); }
inline static ax_ref ax_iter_get  (const ax_iter* it, int i) { return (it)->tr->get((it), i); }
inline static bool   ax_iter_equal(const ax_iter* it1, const ax_iter* it2) { return it1->tr->equal(it1, it2); }
inline static bool   ax_iter_less (const ax_iter* it1, const ax_iter* it2) { return it1->tr->equal(it1, it2); }
inline static size_t ax_iter_dist (const ax_iter* it1, const ax_iter* it2) { return it1->tr->dist(it1, it2); }

#define ax_iter_norm (it)       (ax_step(ax_iter_norm),  ax_iter_norm (it))
#define ax_iter_shift(it, i)    (ax_step(ax_iter_shift), ax_iter_shift((it), (i)))
#define ax_iter_get  (it, i)    (ax_step(ax_iter_get),   ax_iter_get  (it, i))
#define ax_iter_equal(it1, it2) (ax_step(ax_iter_equal), ax_iter_equal(it1, it2))
#define ax_iter_less (it1, it2) (ax_step(ax_iter_less),  ax_iter_less (it1, it2))
#define ax_iter_dist (it1, it2) (ax_step(ax_iter_dist),  ax_iter_dist (it1, it2))

#endif

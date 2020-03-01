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

#ifndef MAP_H_
#define MAP_H_

#include "any.h"
#include "box.h"
#include "debug.h"
#include "pair.h"
struct ax_stuff_trait_st;
typedef struct ax_stuff_trait_st ax_stuff_trait_t;

struct ax_map_st;
typedef struct ax_map_st ax_map_t;

typedef int      (*ax_map_put_f)(ax_any_t* any, ax_cref_t key, ax_cref_t value);
typedef ax_iter_t(*ax_map_get_f)(ax_any_t* any, ax_cref_t key);
typedef ax_bool_t(*ax_map_exist_f)(ax_any_t* any, ax_cref_t key);
typedef ax_iter_t(*ax_map_find_f)(ax_any_t* any, ax_cref_t value);
typedef ax_bool_t(*ax_map_erase_f)(ax_any_t* any, ax_cref_t key);

typedef ax_cref_t (*ax_iter_pairkey_f)(ax_iter_t* it);
typedef ax_ref_t  (*ax_iter_pairval_f)(ax_iter_t* it);

struct ax_map_trait_st
{
	ax_map_put_f put;
	ax_map_get_f get;
	ax_map_exist_f exist;
	ax_map_find_f find;
	ax_map_erase_f erase;
	ax_iter_pairkey_f itkey;
	ax_iter_pairval_f itval;
};
typedef struct ax_map_trait_st ax_map_trait_t;

struct ax_map_st
{
	ax_box_t box;
	const ax_pair_t pair;
	const ax_map_trait_t tr;
	const ax_stuff_trait_t* elem_tr;
};

int       ax_map_put  (ax_any_t* any, ax_ref_t key, ax_ref_t value);
ax_iter_t ax_map_get  (ax_any_t* any, ax_ref_t key);
ax_iter_t ax_map_find (ax_any_t* any, ax_ref_t value);
ax_bool_t ax_map_exist(ax_any_t* any, ax_ref_t key);
ax_bool_t ax_map_erase(ax_any_t* any);
ax_cref_t ax_iter_pair_key(ax_iter_t* it);
ax_ref_t  ax_iter_pair_val(ax_iter_t* it);

#define ax_map_put  (_a, _k, _v) (ax_step(ax_map_put  ), ax_map_put  (_a, _k, _v))
#define ax_map_get  (_a, _k)     (ax_step(ax_map_get  ), ax_map_get  (_a, _k))
#define ax_map_find (_a, _v)     (ax_step(ax_map_find ), ax_map_find (_a, _v))   
#define ax_map_exist(_a, _k)     (ax_step(ax_map_exist), ax_map_exist(_a, _k))  
#define ax_map_erase(_a)         (ax_step(ax_map_erase), ax_map_erase(_a))
#define ax_iter_pair_key(_it)    (ax_step(ax_iter_pair_key), ax_iter_pair_key(_it))
#define ax_iter_pair_val(_it)    (ax_step(ax_iter_pair_val), ax_iter_pair_val(_it))

#endif

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
typedef struct ax_stuff_trait_st ax_stuff_trait;

struct ax_map_st;
typedef struct ax_map_st ax_map;

typedef int     (*ax_map_put_f)  (ax_amap* this, ax_pair pair);
typedef ax_iter (*ax_map_get_f)  (const ax_amap* this, ax_cref key);
typedef bool    (*ax_map_exist_f)(const ax_amap* this, ax_cref key);
typedef ax_iter (*ax_map_find_f) (const ax_amap* this, ax_cref value);
typedef bool    (*ax_map_erase_f)(ax_amap* this, ax_cref key);
typedef ax_pair (*ax_iter_pair_f)(const ax_iter* it);

struct ax_map_trait_st
{
	ax_map_put_f put;
	ax_map_get_f get;
	ax_map_exist_f exist;
	ax_map_find_f find;
	ax_map_erase_f erase;
	ax_iter_pair_f iter_pair;
};
typedef struct ax_map_trait_st ax_map_trait;

struct ax_map_st
{
	ax_box box;
	const ax_map_trait tr;
	const ax_stuff_trait* elem_tr;
};

int     ax_map_put   (ax_amap* this, ax_pair pair)        { return ((ax_map*)this)->tr.put(this, pair); }
ax_iter ax_map_get   (const ax_amap* this, ax_cref key)   { return ((ax_map*)this)->tr.get(this, key); }
ax_iter ax_map_find  (const ax_amap* this, ax_cref value) { return ((ax_map*)this)->tr.find(this, value); }
bool    ax_map_exist (const ax_amap* this, ax_cref key)   { return ((ax_map*)this)->tr.exist(this, key); }
bool    ax_map_erase (ax_amap* this, ax_cref key)         { return ((ax_map*)this)->tr.erase(this, key); }
ax_pair ax_iter_pair (const ax_iter* it)                  { return ((ax_map*)it->owner)->tr.iter_pair(it); }

#define ax_map_put  (this, _k, _v) (ax_step(ax_map_put  ),     ax_map_put  (this, _k, _v))
#define ax_map_get  (this, _k)     (ax_step(ax_map_get  ),     ax_map_get  (this, _k))
#define ax_map_find (this, _v)     (ax_step(ax_map_find ),     ax_map_find (this, _v))   
#define ax_map_exist(this, _k)     (ax_step(ax_map_exist),     ax_map_exist(this, _k))  
#define ax_map_erase(this)         (ax_step(ax_map_erase),     ax_map_erase(this))
#define ax_iter_pair(_it)          (ax_step(ax_iter_pair),     ax_iter_pair(_it))

#endif

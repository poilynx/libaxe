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

#ifndef STR_H_
#define STR_H_
#include "seq.h"
#include "debug.h"
struct ax_str_st;
typedef struct ax_str_st ax_str;

typedef bool     (*ax_str_append_f) (ax_astr* this, ax_cref str);
typedef size_t   (*ax_str_length_f) (ax_astr* this);
typedef bool     (*ax_str_insert_f) (ax_astr* this, int start, ax_cref str);
typedef ax_cref  (*ax_str_cstr_f)   (ax_astr* this);
typedef bool     (*ax_str_comp_f)   (ax_astr* this, const ax_astr* str);
typedef ax_astr* (*ax_str_substr_f) (ax_astr* this, int start, size_t len);
typedef ax_aseq* (*ax_str_split_f)  (ax_astr* this, ax_cref ch);

struct ax_str_trait_st
{
	ax_str_append_f append;
	ax_str_length_f length;
	ax_str_insert_f insert;
	ax_str_cstr_f   cstr;
	ax_str_comp_f   comp;
	ax_str_substr_f substr;
	ax_str_split_f  split;

};
typedef struct ax_str_trait_st ax_str_trait;

struct ax_str_st
{
	ax_seq seq;
	const ax_str_trait* tr;
};

#define ax_str_append(_a, _e)  (ax_step(ax_str_append), ax_str_append
#define ax_str_length(_a)      (ax_step(ax_str_length), ax_str_length
#define ax_str_insert(_a)      (ax_step(ax_str_insert), ax_str_insert
#define ax_str_cstr  (_a)      (ax_step(ax_str_cstr  ), ax_str_cstr  
#define ax_str_comp  (_a)      (ax_step(ax_str_comp  ), ax_str_comp  
#define ax_str_substr(_a)      (ax_step(ax_str_substr), ax_str_substr
#define ax_str_split (_a)      (ax_step(ax_str_split ), ax_str_split 

#endif

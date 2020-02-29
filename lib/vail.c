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

#include "vail.h"
#include "stuff.h"
#include "debug.h"
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define TYPE_ACCEPT(__t) { pos++; term[term_pos].type = (__t); break; }
ax_vaf_t* ax_vaf_make(char *fmt)
{
	struct scan_term_st { char type; char mut; };
	const int term_max = 8;

	ax_vaf_t* vaf = malloc( sizeof(ax_vaf_t) + sizeof(ax_vaf_item_t) * 127);
	if(!vaf) return NULL;

	int varg_count = 0, stuff_count = 0;
	int pos = 0;
	char end = 0;
	while (!end) {
		struct scan_term_st term[term_max];
		int term_pos = 0;
		int repeat = 1;
		int term_len = 0;
		for (;;) {
			switch (fmt[pos]) {
				case '&': term[term_pos].mut = 1; pos++; break;
				default: term[term_pos].mut = 0;
			}
			switch (fmt[pos]) {
				case 'i':
			case 'u':
				pos++;
				switch (fmt[pos]) {
					case '8':
						TYPE_ACCEPT(fmt[pos] == 'i' ? AX_ST_I8 : AX_ST_U8);
					case '1':
						pos++;
						switch (fmt[pos]) {
							case '6':
								TYPE_ACCEPT(fmt[pos] == 'i' ? AX_ST_I16 : AX_ST_U16);
							default:
								goto bad_char;
						}
						break;
					case '3':
						pos++;
						switch (fmt[pos]) {
							case '2':
								TYPE_ACCEPT(fmt[pos] == 'i' ? AX_ST_I32 : AX_ST_U32);
							default:
								goto bad_char;
						}
						break;
					case '6':
						pos++;
						switch (fmt[pos]) {
							case '4':
								TYPE_ACCEPT(fmt[pos] == 'i' ? AX_ST_I64: AX_ST_U64);
							default:
								goto bad_char;
						}
						break;
					default:
						goto bad_char;
				}
				break;
			case 'f':
				TYPE_ACCEPT(AX_ST_F);
			case 'l':
				pos++;
				switch (fmt[pos]) {
					case 'f':
						TYPE_ACCEPT(AX_ST_LF);
					case 'l':
						pos++;
						switch (fmt[pos]) {
							case 'f':
								TYPE_ACCEPT(AX_ST_LLF);
							default:
								goto bad_char;
						}
						break;
					default:
						goto bad_char;
				}
				break;
			case 'p':
				TYPE_ACCEPT(AX_ST_PTR);
			case 'z':
				TYPE_ACCEPT(AX_ST_Z);
			case 's':
				if(term[term_pos].mut == 1) {
					goto bad_char;
				}
				TYPE_ACCEPT(AX_ST_STR);
			default:
				if(isupper((int)fmt[pos])) {
					term[term_pos].type = fmt[pos] - 'A' + AX_ST_PWL;
					TYPE_ACCEPT(AX_ST_PTR);
				}
				if(term_pos == 0 && term[term_pos].mut == 0) {
					goto bad_char;
				}
			}
			switch(fmt[pos]) {
				case '.':
					pos++;
					break;
				default:
					goto end_type_scan;
			}
			term_pos ++;
		} /* end for */

end_type_scan:
		term_len = term_pos + 1;
        switch (fmt[pos]) {
            case 'x':
				pos++;
				if(fmt[pos]>='1' && fmt[pos]<='9') {
					repeat = fmt[pos]-'0';
					pos++;
					while(isdigit((int)fmt[pos])) {
						repeat = repeat * 10 + fmt[pos]-'0';
						if (repeat>12) goto bad_char;
						pos++;
					}
				} else {
					goto bad_char;
				}
		}
		switch (fmt[pos]) {
			case '_':  end = 0; pos++; break;
			case '\0': end = 1; break;
			default:   goto bad_char;
		}

		for(int ri = 0 ; ri < repeat ; ri++) {
			for(int ti = 0 ; ti < term_len ; ti++) {
				char mut = term[ti].mut;
				vaf->table[stuff_count].mut = mut;
				vaf->table[stuff_count].type = term[ti].type;
				varg_count += (!!mut) + 1;
				if(varg_count == 127 && !end) goto too_many_arg;
				stuff_count ++;
			}
		}
	} /* end while */
	vaf->magic = '+';
	vaf->argc = stuff_count;
	vaf = realloc(vaf, sizeof(ax_vaf_t) + sizeof(ax_vaf_item_t) * stuff_count);
	return vaf;
too_many_arg:
	free(vaf);
	ax_perror("too many argument, limited to 127");
	ax_abort();
bad_char:
	free(vaf);
	char badch[3] = {fmt[pos]};
	if (fmt[pos] == '\0')
		badch[0] = '\\', badch[1] = '0';
	(void)badch;
	ax_perror("unexpected #%d character '%s' in format string \"%s\"", pos+1, badch, fmt);
	ax_abort();
	return NULL;
}

void ax_vail_push(ax_vail_t* vail, ax_vail_node_t* node)
{
	assert(vail);
	node->next = NULL;
	if(vail->head == NULL) {
		vail->head = vail->tail = node;
	} else {
		vail->tail->next = node;
		vail->tail = node;
	}
	vail->capacity += node->size;
	vail->size ++;
}

ax_vail_node_t* ax_vail_pop(ax_vail_t* vail)
{
	assert(vail);
	ax_vail_node_t* head = vail->head;
	if(vail->head == NULL) {
		return NULL;
	} else {
		vail->head = vail->head->next;
		vail->size--;
		return head;
	}
}

ax_vail_t* ax_vail_read(ax_vaf_t* vaf, ...)
{
	va_list va;
	va_start(va, vaf);

	ax_vail_t* vail = malloc(sizeof(ax_vail_t));
	vail->size = 0;
	vail->capacity = 0;
	vail->head = NULL;
	vail->tail = NULL;

	for (int node_i = 0 ; node_i < vaf->argc ; node_i++) {
		ax_vail_node_t* node = malloc(sizeof(ax_vail_node_t));
		if (vaf->table[node_i].mut) {
			void* arr_ptr = va_arg(va, void*);
			size_t arr_elems = va_arg(va, size_t);
			size_t arr_size = arr_elems * ax_stuff_size(vaf->table[node_i].type);

			node->type = vaf->table[node_i].type;
			node->value.ptr = arr_ptr;
			node->mut = 1;
			node->size = arr_size;
			vail->capacity += arr_size;
		} else {
			switch (vaf->table[node_i].type) {
				case AX_ST_I8:  node->value.i8 = (int8_t)va_arg(va, int32_t); break;
				case AX_ST_I16: node->value.i16 = (int16_t)va_arg(va, int32_t); break;
				case AX_ST_I32: node->value.i32 = va_arg(va, int32_t); break;
				case AX_ST_I64: node->value.u64 = va_arg(va, int64_t); break;
				case AX_ST_U8:  node->value.u8  = (uint8_t)va_arg(va, uint32_t); break;
				case AX_ST_U16: node->value.u16 = (uint16_t)va_arg(va, uint32_t); break;
				case AX_ST_U32: node->value.u32 = va_arg(va, uint32_t); break;
				case AX_ST_U64: node->value.u64 = va_arg(va, uint64_t); break;
				case AX_ST_Z:   node->value.z   = (float)va_arg(va, size_t); break;
				case AX_ST_F:   node->value.f   = (float)va_arg(va, double); break;
				case AX_ST_LF:  node->value.lf  = va_arg(va, double); break;
				case AX_ST_LLF: node->value.llf = va_arg(va, long double); break;
				case AX_ST_PTR: node->value.ptr = va_arg(va, void*);
								break;
				case AX_ST_STR: node->value.str = va_arg(va, char*);
								node->size = strlen(node->value.str)+1;
								break;
			}
			node->type = vaf->table[node_i].type;
			node->size = ax_stuff_size(node->type);
			node->mut = 0;
			vail->capacity += node->size;
		}
		ax_vail_push(vail, node);
	} /* end for */
	va_end(va);
	return vail;
}

void ax_vail_free(ax_vail_t* vail) {
	ax_vail_node_t* p = ax_vail_pop(vail);
	while (p) {
		free(p);
		p = ax_vail_pop(vail);
	}
	free(vail);
}

#include <stdio.h>
void test() {
	ax_vaf_t* vaf = ax_vaf_make("llf_i8_&i8.sx3_i32");
	printf("argc = %hhd\n", vaf->argc);
	for(int i = 0; i< vaf->argc; i++) {
		printf("%s %hhd\n", ax_stuff_name(vaf->table[i].type), vaf->table[i].mut);
	}
	//ax_vail_t* vail = ax_vail_
}

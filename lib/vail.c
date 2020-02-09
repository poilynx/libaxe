#include "vail.h"
#include "basic.h"
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#define TYPE_ACCEPT(__t) { pos++; type = (__t); break; }
ax_vaf_t* ax_vaf_make(char *fmt)
{
	ax_vaf_t* vaf = malloc( sizeof(ax_vaf_t) + sizeof(ax_vaf_item_t) * 127);
	if(!vaf) return NULL;

	uint32_t node_count = 0;
	uint32_t varg_count = 0;
	int pos = 0;
	char end = 0;
	while (!end) {
		ax_bool_t mutab = 0;
		ax_basic_type_t type = AX_BT_RAW;
		char label = '-';
		size_t repeat = 1;

		switch (fmt[pos]) {
			case '&': mutab = 1; pos++;
		}
		switch (fmt[pos]) {
			case 'i':
			case 'u':
				pos++;
				switch (fmt[pos]) {
					case '8':
						TYPE_ACCEPT(fmt[pos] == 'i' ? AX_BT_I8 : AX_BT_U8);
					case '1':
						pos++;
						switch (fmt[pos]) {
							case '6':
								TYPE_ACCEPT(fmt[pos] == 'i' ? AX_BT_I16 : AX_BT_U16);
							default:
								goto bad_char;
						}
						break;
					case '3':
						pos++;
						switch (fmt[pos]) {
							case '2':
								TYPE_ACCEPT(fmt[pos] == 'i' ? AX_BT_I32 : AX_BT_U32);
							default:
								goto bad_char;
						}
						break;
					case '6':
						pos++;
						switch (fmt[pos]) {
							case '4':
								TYPE_ACCEPT(fmt[pos] == 'i' ? AX_BT_I64: AX_BT_U64);
							default:
								goto bad_char;
						}
						break;
					default:
						goto bad_char;
				}
				break;
			case 'f':
				TYPE_ACCEPT(AX_BT_F);
			case 'l':
				pos++;
				switch (fmt[pos]) {
					case 'f':
						TYPE_ACCEPT(AX_BT_LF);
					case 'l':
						switch (fmt[pos]) {
							case 'f':
								TYPE_ACCEPT(AX_BT_LLF);
							default:
								goto bad_char;
						}
						break;
					default:
						goto bad_char;
				}
				break;
			case 'p':
				TYPE_ACCEPT(AX_BT_PTR);
			case 'z':
				TYPE_ACCEPT(AX_BT_Z);
            case 's':
				if(mutab == 1) {
					goto bad_char;
					break;
				}
				TYPE_ACCEPT(AX_BT_STR);
			default:
				if(isupper(fmt[pos])) {
					label = fmt[pos];
					TYPE_ACCEPT(AX_BT_PTR);
				}
				if(mutab == 0) {
					goto bad_char;
					break;
				}
		}
        switch (fmt[pos]) {
            case 'x':
				pos++;
				if(fmt[pos]>='1' && fmt[pos]<='9') {
					repeat = fmt[pos]-'0';
					pos++;
					while(isdigit(fmt[pos])) {
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

		vaf->table[node_count].mut = mutab;
		vaf->table[node_count].type = type;
		vaf->table[node_count].label = label;
		vaf->table[node_count].repeat = repeat;
		node_count ++;
		varg_count += (!!mutab) + 1;
		if(varg_count = 127 && !end) goto too_many_arg;
	}
	vaf->magic = '+';
	vaf->argc = node_count;
	vaf = realloc(vaf, sizeof(ax_vaf_t) + sizeof(ax_vaf_item_t) * node_count);
	return vaf;
too_many_arg:
	free(vaf);
	ax_fault("too many argument, limited to 127");
bad_char:
	free(vaf);
	ax_fault("unexpected #%d character '%c' in format string\"%s\"", pos+1, fmt[pos], fmt);
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
		for (int rep_i = 0 ; rep_i < vaf->table[node_i].repeat; rep_i++) {
			ax_vail_node_t* node = malloc(sizeof(ax_vail_node_t));
			if (vaf->table[node_i].mut) {
				void* arr_ptr = va_arg(va, void*);
				size_t arr_elems = va_arg(va, size_t);
				size_t arr_size = arr_elems * ax_basic_size(vaf->table[node_i].type);

				node->type = vaf->table[node_i].type;
				node->label = vaf->table[node_i].label;
				node->value.ptr = arr_ptr;
				node->mut = 1;
				node->size = arr_size;
				vail->capacity += arr_size;
			} else {
				switch (vaf->table[node_i].type) {
					case AX_BT_I8:  node->value.i8 = (int8_t)va_arg(va, int32_t); break;
					case AX_BT_I16: node->value.i16 = (int16_t)va_arg(va, int32_t); break;
					case AX_BT_I32: node->value.i32 = va_arg(va, int32_t); break;
					case AX_BT_I64: node->value.u64 = va_arg(va, int64_t); break;
					case AX_BT_U8:  node->value.u8  = (uint8_t)va_arg(va, uint32_t); break;
					case AX_BT_U16: node->value.u16 = (uint16_t)va_arg(va, uint32_t); break;
					case AX_BT_U32: node->value.u32 = va_arg(va, uint32_t); break;
					case AX_BT_U64: node->value.u64 = va_arg(va, uint64_t); break;
					case AX_BT_Z:   node->value.z   = (float)va_arg(va, size_t); break;
					case AX_BT_F:   node->value.f   = (float)va_arg(va, double); break;
					case AX_BT_LF:  node->value.lf  = va_arg(va, double); break;
					case AX_BT_LLF: node->value.llf = va_arg(va, long double); break;
					case AX_BT_PTR: node->value.ptr = va_arg(va, void*);
									break;
					case AX_BT_STR: node->value.str = va_arg(va, char*);
									node->size = strlen(node->value.str)+1;
									break;
				}
				node->type = vaf->table[node_i].type;
				node->label = vaf->table[node_i].label;
				node->size = ax_basic_size(node->type);
				node->mut = 0;
				vail->capacity += node->size;
			}
			ax_vail_push(vail, node);
		}
	}
	va_end(va);
	return vail;
}

void ax_vail_free(ax_vail_t* vail) {
	ax_vail_t* p = ax_vail_pop(vail);
	while (p) {
		free(p);
		p = ax_vail_pop(vail);
	}
	free(vail);
}


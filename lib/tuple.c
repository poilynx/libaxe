#include "tuple.h"
#include "basic.h"
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

struct node_st
{
	char type;
	char mutable;
	char label;
	union {
		ax_basic_t basic;
		void* array;
	};
	size_t size;
	struct node_st* next;
};

struct stack_st
{
	size_t size;
	struct node_st* list;
	size_t stash_size;
};
typedef struct stack_st stack_t;

static void stack_init(stack_t* s)
{
	s->size = 0;
	s->list = NULL;
	s->stash_size;
}

static void stack_push(stack_t* s, struct node_st* node)
{
	assert(s);
	node->next = s->list;
	s->list = node;
	s->size ++;
}

static struct node_st* stack_pop(stack_t* s)
{
	assert(s);
	struct node_st* ret = s->list;
	if(s->list != NULL) {
		s->list = s->list->next;
		s->size--;
	}
	return ret;
}

static ax_tuple_t* stack_to_tuple(stack_t* s)
{
	ax_tuple_t* t = malloc(sizeof(ax_tuple_t));
	t->item_tab = malloc(sizeof(ax_tuple_item_t) * s->size);
	t->stash = malloc(s->stash_size);
	t->size = s->size;

	void* stash_pos = t->stash;
	struct node_st* p = s->list;
	size_t i;
	for (i=s->size-1; p; p=p->next, i--) {
		t->item_tab[i].ptr = stash_pos;
		t->item_tab[i].type = p->type;
		t->item_tab[i].label = p->label;
		if (p->mutable) {
			t->item_tab[i].flag = AX_TF_MUTABLE;
			t->item_tab[i].count = p->size;
			memcpy(stash_pos, p->array, p->size);
			stash_pos += p->size;
		} else {
			t->item_tab[i].flag = 0;
			t->item_tab[i].count = 1;
			memcpy(stash_pos, &(p->basic), p->size);
			stash_pos += p->size;
		}
	}
	printf("%zu\n", i+1);
	return t;
}

static void stack_clear(stack_t* s)
{
	while (s->list) {
		struct node_st* p = s->list;
		s->list = s->list->next;
		free(p);
	}
}

#define TYPE_ACCEPT(__t) { pos++; type = (__t); break; }
#define REJECT() { fail = 1; break; }
ax_tuple_t* ax_tuple_alloc(char* layout, ...)
{
	va_list va;
	va_start(va, layout);

	stack_t stack;
	stack_init(&stack);
	int pos = 0;
	char fail = 0, end = 0;
	while (!end) {
		char isarray = 0;
		switch (layout[pos]) {
			case '&': isarray = 1; pos++;
		}
		ax_basic_type_t type = AX_BT_RAW;
		char label = '-';
		switch (layout[pos]) {
			case 'i':
			case 'u':
				pos++;
				switch (layout[pos]) {
					case '8':
						TYPE_ACCEPT(layout[pos] == 'i' ? AX_BT_I8 : AX_BT_U8);
					case '1':
						pos++;
						switch (layout[pos]) {
							case '6':
								TYPE_ACCEPT(layout[pos] == 'i' ? AX_BT_I16 : AX_BT_U16);
							default:
								REJECT();
						}
						break;
					case '3':
						pos++;
						switch (layout[pos]) {
							case '2':
								TYPE_ACCEPT(layout[pos] == 'i' ? AX_BT_I32 : AX_BT_U32);
							default:
								REJECT();
						}
						break;
					case '6':
						pos++;
						switch (layout[pos]) {
							case '4':
								TYPE_ACCEPT(layout[pos] == 'i' ? AX_BT_I64: AX_BT_U64);
							default:
								REJECT();
						}
						break;
					default:
						REJECT();
				}
				break;
			case 'f':
				TYPE_ACCEPT(AX_BT_F);
			case 'l':
				pos++;
				switch (layout[pos]) {
					case 'f':
						TYPE_ACCEPT(AX_BT_LF);
					case 'l':
						switch (layout[pos]) {
							case 'f':
								TYPE_ACCEPT(AX_BT_LLF);
							default:
								REJECT();
						}
						break;
					default:
						REJECT();
				}
				break;
			case 'p':
				TYPE_ACCEPT(AX_BT_PTR);
			case 'z':
				TYPE_ACCEPT(AX_BT_Z);
            case 's':
				if(isarray == 1) {
					REJECT();
					break;
				}
				TYPE_ACCEPT(AX_BT_STR);
			default:
				if(isupper(layout[pos])) {
					label = layout[pos];
					TYPE_ACCEPT(AX_BT_PTR);
				}
				if(isarray == 0) {
					REJECT();
					break;
				}
		}
		if (fail) goto failed;

		size_t repeat = 1;
        switch (layout[pos]) {
            case 'x':
				pos++;
				if(layout[pos]>='1' && layout[pos]<='9') {
					repeat = layout[pos]-'0';
					pos++;
					while(isdigit(layout[pos])) {
						repeat = repeat * 10 + layout[pos]-'0';
						if (repeat>12) REJECT();
						pos++;
					}
				} else {
					REJECT();
				}
		}
		if(fail) goto failed;

		switch (layout[pos]) {
			case '_':  end = 0; pos++; break;
			case '\0': end = 1; break;
			default:   REJECT();
		}
		if(fail) goto failed;

		for (int i = 0; i<repeat; i++) {
			struct node_st* item = malloc(sizeof(struct node_st));
			item->type = type;
			item->label = label;
			if (isarray) {
				void* arr_ptr = va_arg(va, void*);
				size_t arr_elems = va_arg(va, size_t);
				item->array = arr_ptr;
				item->mutable = 1;
				size_t arr_size = arr_elems * ax_basic_size(type);
				item->size = arr_size;
				stack.stash_size += arr_size;
			} else {
				item->size = ax_basic_size(item->type);
				switch (type) {
					case AX_BT_I8:  item->basic.i8 = (int8_t)va_arg(va, int32_t); break;
					case AX_BT_I16: item->basic.i16 = (int16_t)va_arg(va, int32_t); break;
					case AX_BT_I32: item->basic.i32 = va_arg(va, int32_t); break;
					case AX_BT_I64: item->basic.u64 = va_arg(va, int64_t); break;
					case AX_BT_U8:  item->basic.u8  = (uint8_t)va_arg(va, uint32_t); break;
					case AX_BT_U16: item->basic.u16 = (uint16_t)va_arg(va, uint32_t); break;
					case AX_BT_U32: item->basic.u32 = va_arg(va, uint32_t); break;
					case AX_BT_U64: item->basic.u64 = va_arg(va, uint64_t); break;
					case AX_BT_Z:   item->basic.z   = (float)va_arg(va, size_t); break;
					case AX_BT_F:   item->basic.f   = (float)va_arg(va, double); break;
					case AX_BT_LF:  item->basic.lf  = va_arg(va, double); break;
					case AX_BT_LLF: item->basic.llf = va_arg(va, long double); break;
					case AX_BT_PTR: item->basic.ptr = va_arg(va, void*);
									break;
					case AX_BT_STR: item->basic.str = va_arg(va, char*);
									item->size = strlen(item->basic.str)+1;
									break;
				}
				item->mutable = 0;
				stack.stash_size += item->size;
			}
			stack_push(&stack, item);
		}
	}
	va_end(va);
	ax_tuple_t* t = stack_to_tuple(&stack);
	stack_clear(&stack);
	return t;
failed:
		ax_fault("unexpected #%d character '%c' in layout \"%s\"", pos+1, layout[pos], layout);
}


#include "tuple.h"
#include "basic.h"
#include <ctype.h>
#include <stdarg.h>

struct node_st
{
	ax_basic_type_t type;
	union {
		ax_basic_t value;
		void* array;
	};
	size_t size;
	struct node_st* next;
}
typedef struct node_st *stack_t;

static void stack_push(stack_t *s, struct node_st* node)
{
	assert(s);
	node->next = *s;
	*s = node;
}

static struct node_st* stack_pop(stack_t *s)
{
	assert(s);
	struct node_st *ret = *s;
	if(*s != NULL)
		*s = (*s)->next;
	return ret;
}
#define TYPE_ACCEPT(type) { pos++; item->type = type; break; }
#define REJECT() { fail = 1; break; }
stack_t parse_layout(unsigned char* layout)
{
	}

ax_tuple_t* ax_tuple_alloc(char* layout, ...)
{

	va_list va;
	va_start(va, layout);

	ax_basic_h val;
	stack_t stack = NULL;
	int pos = 0;
	char fail = 0;
	char end = 0;
	while (!end) {
		struct node_st* item = malloc(sizeof(struct node_st));
		char isarray = 0;
		switch (layout[pos]) {
			case '&': isarray = 1; pos++;
		}
		ax_basic_type_t item->type;
		pos_begin = pos;
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
						switch (layout[pos]) {
							case '2':
								TYPE_ACCEPT(layout[pos] == 'i' ? AX_BT_I32 : AX_BT_U32);
							default:
								REJECT();
						}
						break;
					case '6':
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
				TYPE_ACCESS(AX_BT_STR);
			default:
				if(isarray == 0) {
					REJECT();
					break;
				}
		}
		if (fail) goto failed;

		size_t repeat = 0;
        switch (layout[pos]) {
            case 'x':
				pos++;
				if(layout[pos]>=1 && layout[pos]<=9) {
					repeat = layout[pos]-'0';
					while(isdigit(layout[pos])) {
						repeat = repeat * 10 + layout[pos]-'0';
						pos++;
					}
				} else {
					REJECT();
				}
			default:
		}
		if(fail) goto failed;

		switch (layout[pos]) {
			case '_': end = false;
			case '\0': end = true;
			default:
				REJECT();
		}
		if(fail) goto failed;

		if (isarray) {
			switch (item->type) {
				case AX_BT_I8:  
					basic->i8 = (int8_t)va_arg(va, int32_t);
					break;
				case AX_BT_I16: basic->i16 = (int16_t)va_arg(va, int32_t); break;
				case AX_BT_I32: basic->i32 = va_arg(va, int32_t); break;
				case AX_BT_I64: basic->u64 = va_arg(va, int64_t); break;
				case AX_BT_U8:  basic->u8  = (uint8_t)va_arg(va, uint32_t); break;
				case AX_BT_U16: basic->u16 = (uint16_t)va_arg(va, uint32_t); break;
				case AX_BT_U32: basic->u32 = va_arg(va, uint32_t); break;
				case AX_BT_U64: basic->u64 = va_arg(va, uint64_t); break;
				case AX_BT_Z:   basic->z   = (float)va_arg(va, size_t); break;
				case AX_BT_F:   basic->f   = (float)va_arg(va, double); break;
				case AX_BT_LF:  basic->lf  = va_arg(va, double); break;
				case AX_BT_LLF: basic->llf = va_arg(va, long double); break;
				case AX_BT_PTR: basic->ptr = va_arg(va, void*); break;
				case AX_BT_RAW: 
			}

		} else {
			switch (item->type) {
				case AX_BT_I8:  
					basic->i8 = (int8_t)va_arg(va, int32_t);
					break;
				case AX_BT_I16: basic->i16 = (int16_t)va_arg(va, int32_t); break;
				case AX_BT_I32: basic->i32 = va_arg(va, int32_t); break;
				case AX_BT_I64: basic->u64 = va_arg(va, int64_t); break;
				case AX_BT_U8:  basic->u8  = (uint8_t)va_arg(va, uint32_t); break;
				case AX_BT_U16: basic->u16 = (uint16_t)va_arg(va, uint32_t); break;
				case AX_BT_U32: basic->u32 = va_arg(va, uint32_t); break;
				case AX_BT_U64: basic->u64 = va_arg(va, uint64_t); break;
				case AX_BT_Z:   basic->z   = (float)va_arg(va, size_t); break;
				case AX_BT_F:   basic->f   = (float)va_arg(va, double); break;
				case AX_BT_LF:  basic->lf  = va_arg(va, double); break;
				case AX_BT_LLF: basic->llf = va_arg(va, long double); break;
				case AX_BT_PTR: basic->ptr = va_arg(va, void*); break;
				case AX_BT_STR:

			}

		}
		continue;
failed:
		free(item);
		fault("unexpected #%d character '%c' in layout \"%s\"", pos+1, layout);
	}


}

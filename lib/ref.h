#ifndef REF_H_
#define REF_H_
#include <stdarg.h>
#include "base.h"
#include "basic.h"
//struct ax_box_st;
//typedef struct ax_box_st ax_box_t;
struct ax_ref_st
{
	ax_basic_type_t type;
	void *ptr;
};
typedef struct ax_ref_st ax_ref_t;


int8_t   ax_ref_toi8 (ax_ref_t r);
int16_t  ax_ref_toi16(ax_ref_t r);
int32_t  ax_ref_toi32(ax_ref_t r);
int64_t  ax_ref_toi64(ax_ref_t r);
uint8_t  ax_ref_tou8 (ax_ref_t r);
uint16_t ax_ref_tou16(ax_ref_t r);
uint32_t ax_ref_tou32(ax_ref_t r);
uint64_t ax_ref_tou64(ax_ref_t r);
float    ax_ref_tof  (ax_ref_t r);
double   ax_ref_tolf (ax_ref_t r);
char*    ax_ref_tostr(ax_ref_t r);
void*    ax_ref_toptr(ax_ref_t r);

#endif

#ifndef REF_H_
#define REF_H_
#include "def.h"
#include "basic.h"
#include <stdarg.h>
struct ax_ref_st
{
	void *ptr;
#ifndef NDEBUG
	char type;
	char mut;
#endif
};
typedef struct ax_ref_st ax_ref_t;

int8_t      ax_ref_i8 (ax_ref_t r);
int16_t     ax_ref_i16(ax_ref_t r);
int32_t     ax_ref_i32(ax_ref_t r);
int64_t     ax_ref_i64(ax_ref_t r);
uint8_t     ax_ref_u8 (ax_ref_t r);
uint16_t    ax_ref_u16(ax_ref_t r);
uint32_t    ax_ref_u32(ax_ref_t r);
uint64_t    ax_ref_u64(ax_ref_t r);
float       ax_ref_f  (ax_ref_t r);
double      ax_ref_lf (ax_ref_t r);
long double ax_ref_llf(ax_ref_t r);
void*       ax_ref_ptr(ax_ref_t r);
char*       ax_ref_str(ax_ref_t r);

int8_t*      ax_ref_pi8 (ax_ref_t r);
int16_t*     ax_ref_pi16(ax_ref_t r);
int32_t*     ax_ref_pi32(ax_ref_t r);
int64_t*     ax_ref_pi64(ax_ref_t r);
uint8_t*     ax_ref_pu8 (ax_ref_t r);
uint16_t*    ax_ref_pu16(ax_ref_t r);
uint32_t*    ax_ref_pu32(ax_ref_t r);
uint64_t*    ax_ref_pu64(ax_ref_t r);
float*       ax_ref_pf  (ax_ref_t r);
double*      ax_ref_plf (ax_ref_t r);
long double* ax_ref_pllf(ax_ref_t r);
void**       ax_ref_pptr(ax_ref_t r);
void*        ax_ref_raw (ax_ref_t r);

#endif

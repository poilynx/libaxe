#include "axe.h"
#include "vector.h"
#include <stdio.h>
#include <inttypes.h>

#define FOR_EACH(_it, _a) \
	for ( ax_iter_t _it = ax_box_begin((_a)), __##_it##_end = ax_box_end((_a)); \
			!ax_iter_equal(&(_it), &(__##_it##_end)) ; \
			ax_iter_shift(&it, 1))
int main() {
	ax_init();
	ax_vector_t vec;
	ax_any_t* a = ax_vector_create(&vec, ax_stuff_trait(AX_ST_I32));

	int32_t i;
	i = 7;
	ax_seq_push(a, &i);
	i = 8;
	ax_seq_push(a, &i);
	i = 9;
	ax_seq_push(a, &i);

	printf("size = %zu\n", ax_box_size(a));

	//FOR_EACH(it, a) {
	//	ax_ref_t r = ax_iter_get(&it, 0);
	//	printf("elem = %" PRId32 "\n", *ax_ref_pi32(r));
	//}

	//printf("size = %zu\n", ax_box_size(a));
	
	ax_iter_t it = ax_box_rbegin(a);
	ax_iter_t it_end = ax_box_end(a);
	while (!ax_iter_equal(&it, &it_end)) {
		ax_ref_t r = ax_iter_get(&it, 0);
		printf("elem = %" PRId32 "\n", *ax_ref_pi32(r));
		it = ax_box_erase(a, &it);
	}
	printf("size = %zu\n", ax_box_size(a));

	ax_any_free(a);

	return 0;
}

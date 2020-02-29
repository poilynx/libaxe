#include "axe.h"
#include "vector.h"
#include "debug.h"
#include <stdio.h>
#include <inttypes.h>
int main() {
	ax_init();
	ax_vector_t vec;
	ax_any_t* a = ax_vector_create(&vec, ax_stuff_trait(AX_ST_I32));

	int32_t i;
	i = 7;
	ax_seq_push(a, ax_rset_i32(&i));
	i = 8;
	ax_seq_push(a, ax_rset_i32(&i));
	i = 9;
	ax_seq_push(a, ax_rset_i32(&i));

	printf("size = %zu\n", ax_box_size(a));

	ax_foreach(r, a) {
		printf("elem = %" PRId32 "\n", ax_rget_i32(r));
	}

	printf("size = %zu\n", ax_box_size(a));
	
	ax_iter_t it = ax_box_begin(a);
	ax_iter_t it_end = ax_box_end(a);
	while (!ax_iter_equal(&it, &it_end)) {
		ax_ref_t r = ax_iter_get(&it, 0);
		printf("elem = %" PRId32 "\n", ax_rget_i32(r));
		ax_box_erase(a, &it);
		it_end = ax_box_end(a);
	}
	printf("size = %zu\n", ax_box_size(a));

	ax_any_free(a);

	ax_uninit();

	return 0;

}

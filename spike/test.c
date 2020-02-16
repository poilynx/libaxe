#include "vector.h"
#include <stdio.h>
#include <inttypes.h>
int main() {
	ax_vector_t vec;
	ax_any_t* a = ax_vector_create(&vec, ax_basic_get_trait(AX_BT_I32));

	int32_t i;
	i = 7;
	ax_seq_push(a, &i);
	i = 8;
	ax_seq_push(a, &i);
	i = 9;
	ax_seq_push(a, &i);

	printf("size = %zu\n", ax_box_size(a));

	ax_iter_t it = ax_box_begin(a);
	ax_iter_t it_end = ax_box_end(a);

	for ( ; !ax_iter_equal(&it, &it_end) ; ax_iter_shift(&it, 1) ) {
		ax_ref_t r = ax_iter_get(&it);
		printf("elem = %" PRId32 "\n", *ax_ref_pi32(r));
	}

	ax_free(a);

	return 0;
}

/* Output:

# gcc test.c -laxe -L. -g -DAX_TRACE && ./a.exe
ax:trace:test.c:main:9: call ax_seq_push
ax:trace:test.c:main:11: call ax_seq_push
ax:trace:test.c:main:13: call ax_seq_push
ax:trace:test.c:main:15: call ax_box_size
size = 3
ax:trace:test.c:main:17: call ax_box_begin
ax:trace:test.c:main:18: call ax_box_end
ax:trace:test.c:main:20: call ax_iter_equal
ax:trace:test.c:main:21: call ax_iter_get
elem = 7
ax:trace:test.c:main:20: call ax_iter_shift
ax:trace:test.c:main:20: call ax_iter_equal
ax:trace:test.c:main:21: call ax_iter_get
elem = 8
ax:trace:test.c:main:20: call ax_iter_shift
ax:trace:test.c:main:20: call ax_iter_equal
ax:trace:test.c:main:21: call ax_iter_get
elem = 9
ax:trace:test.c:main:20: call ax_iter_shift
ax:trace:test.c:main:20: call ax_iter_equal
ax:trace:test.c:main:25: call ax_free

*/


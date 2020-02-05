#include <stdio.h>
#include <assert.h>
#include "base.h"
int main() {
	//ax_fault("hello");
	ax_assert(0, "hello %d", 1);
	return 0;
}

#include "CuTest.h"
#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CompareAsserts(tc, message, expected, actual)  X_CompareAsserts((tc), __FILE__, __LINE__, (message), (expected), (actual))

static void X_CompareAsserts(CuTest* tc, const char *file, int line, const char* message, const char* expected, const char* actual)
{
	int mismatch;
	if (expected == NULL || actual == NULL) {
		mismatch = (expected != NULL || actual != NULL);
	} else {
		const char *front = __FILE__ ":";
		const size_t frontLen = strlen(front);
		const size_t expectedLen = strlen(expected);

		const char *matchStr = actual;

		mismatch = (strncmp(matchStr, front, frontLen) != 0);
		if (!mismatch) {
			matchStr = strchr(matchStr + frontLen, ':');
			mismatch |= (matchStr == NULL || strncmp(matchStr, ": ", 2));
			if (!mismatch) {
				matchStr += 2;
				mismatch |= (strncmp(matchStr, expected, expectedLen) != 0);
			}
		}
	}

	CuAssert_Line(tc, file, line, message, !mismatch);
}

void TestTuple(CuTest* tc)
	int32_t arr[3] = {1, 2, 3};
	char *str = "hello world";
	int raw = 1;
	char *layout = "&i32x3_i8_s_&_A";
	void *p1 = (void*)1;
	ax_tuple_t* t = ax_tuple_alloc(layout,
			&arr, (size_t)3,
			&arr, (size_t)3,
			&arr, (size_t)3,
			10,
			str,
			&raw, sizeof(raw),
			p1
	);
	printf("layout = %s\n", layout);
	printf("size = %zu\n", t->size);
	for(int i=0; i<t->size; i++) {
		printf("count:%zu flag:%hhd label:%c type:%s\n",
				t->item_tab[i].count,
				t->item_tab[i].flag,
				t->item_tab[i].label,
				ax_basic_name(t->item_tab[i].type)
			  );
	}
	///....
}

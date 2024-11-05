#include <stdio.h>
#include <stdint.h>

long get_val(long ago[5][2], int index, int index2) {
	return ago[index][index2];
}

int main(void) {
	int a[5];

	printf("%p\n%p\n%p\n%p\n%p\n",
			a,
			a + 1,
			&a[2],
			&a[3],
			&a[4]);
	return 0;
}

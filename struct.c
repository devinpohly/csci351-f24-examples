#include <stdio.h>
#include <stdint.h>

struct foo {
	int x;
	// 4 pad
	long y;
	int z;
	// 4 pad
};

int main(void) {
	struct foo f;

	printf("%d\n", sizeof(f));
	printf("%p\n%p\n%p\n%p\n",
			&f.x,
			&f.y,
			&f.z);
	return 0;
}

#include <stdio.h>
#include <stdint.h>

struct foo {
	int x;
	// 4 pad
	long y;
	int z;
	// 4 pad
};

void other1(void) {
	int arr[20];
	for (int i = 0; i < 20; i++) {
		arr[i] = i * i + 3;
	}
}

void other(void) {
	struct foo f;
	f.x = 1;
	f.y = 2;
	f.z = 3;

	printf("x = %d\ny = %ld\nz = %d\n", f.x, f.y, f.z);
	//int *pad1 = (int *) (((char * ) &f) + 4);
	int *pad1 = &f.x + 1;
	int *pad2 = &f.z + 1;
	printf("pad1 = %d\npad2 = %d\n", *pad1, *pad2);
}

int main(void) {
	printf("hello world %d\n", 100);
	other1();
	other();

	return 0;
}

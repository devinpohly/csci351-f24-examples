#include <stdio.h>

union foo {
	int x;
	char y[9];
	unsigned long z;
};

int main(void)
{
	union foo f;

	f.x = 0x71424831;
	printf("%d\n", f.x);
	printf("%s\n", f.y);
	printf("%ld\n", f.z);

	printf("%p %p %p\n", &f.x, &f.y, &f.z);
	printf("%ld\n", sizeof(f));

	return 0;
}

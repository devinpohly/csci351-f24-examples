#include <stdio.h>
#include <stdlib.h>

int g = 5;
int arr[1999];

void foo(int x) {
	static int y = 2;
	printf("%d\n", x * y);
	printf("Argument: %p\n", &x);
	printf("Static local: %p\n", &y);
	printf("y is %d\n", y);
	y++;
}

int main(void) {
	int x = 10;
	printf("Local: %p\n", &x);
	printf("Global: %p\n", &g);
	foo(x);
	foo(x);
	foo(x);

	int *p = malloc(sizeof(int));
	*p = 15;
	printf("Dynamic: %p\n", p);
	printf("Local: %p\n", &p);

	printf("foo: %p\n", &foo);
	printf("main: %p\n", &main);
	printf("printf: %p\n", &printf);
	return 0;
}

#include <stdio.h>

long multiply(long x, long y) {
	return x * y;
}

void multiply_store(long a, long b, long *p) {
	*p = multiply(b, a);
}

void print_squares() {
	int squares[20];
	for (int i = 0; i < 20; i++) {
		squares[i] = i * i;
	}

	for (int i = 0; i < 20; i++ ) {
		printf("%d\n", squares[i]);
	}
}

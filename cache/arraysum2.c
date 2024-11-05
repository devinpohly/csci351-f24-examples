#include <stdio.h>
#include <stdlib.h>

#define DIM 30000

long *element(long *arr, int r, int c) {
	return &arr[r * DIM + c];
}

int main(int argc, char **argv)
{
	long *mat = malloc(sizeof(long) * DIM * DIM);

	for (int j = 0; j < DIM; j++) {
		for (int i = 0; i < DIM; i++) {
			*element(mat, i, j) = i * j;
		}
	}

	long total = 0;
	for (int j = 0; j < DIM; j++) {
		for (int i = 0; i < DIM; i++) {
			total += *element(mat, i, j);
		}
	}

	printf("%ld\n", total);
	return 0;
}

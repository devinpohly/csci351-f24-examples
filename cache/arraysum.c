#include <stdio.h>
#include <stdlib.h>

#define DIM 30000

long *element(long *arr, int r, int c) {
	return &arr[r * DIM + c];
}

int main(int argc, char **argv)
{
	long *mat = malloc(sizeof(long) * DIM * DIM);

	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			*element(mat, i, j) = i * j;
		}
	}

	long total = 0;
	for (int i = 0; i < DIM; i++) {
		for (int j = 0; j < DIM; j++) {
			total += *element(mat, i, j);
		}
	}

	printf("%ld\n", total);
	return 0;
}

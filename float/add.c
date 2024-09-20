#include <stdio.h>

int main(void)
{
	float f = 100000000.0;

	for (int i = 0; i < 1000000000; i++) {
		f += 1.0;
	}

	printf("%f\n", f);

	f *= 2;

	printf("%f\n", f);

	return 0;
}

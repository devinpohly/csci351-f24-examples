#include <stdio.h>

int main(void) {
	int x, y;
	char name[10];

	sscanf("3 2 hello", "%d %d %s", &x, &y, name);

	printf("%d\n%d\n%s\n", x, y, name);

	return 0;
}

#include <stdio.h>

int main(void) {
	FILE *f = fopen("test.txt", "r+");
	char name[100];
	fscanf(f, "Hello %s", name);
	fprintf(f, "Your name was %s\n", name);
	fflush(f);
	fclose(f);
	return 0;
}

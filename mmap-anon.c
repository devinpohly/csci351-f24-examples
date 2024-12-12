#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	unsigned char *data = mmap(NULL, 1024, PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (data == MAP_FAILED) {
		perror("mmap");
		return 1;
	}

	fork();

	/* for (int i = 0; i < 16; i++) { */
	/* 	printf("%02hhx ", data[i]); */
	/* } */
	/* printf("\n"); */

	data[1]++;

	for (int i = 0; i < 16; i++) {
		printf("%02hhx ", data[i]);
	}
	printf("\n");

	return 0;
}

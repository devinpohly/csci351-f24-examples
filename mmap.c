#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd = open("test.dat", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return 1;
	}

	unsigned char *data = mmap(NULL, 1024, PROT_READ,
			MAP_SHARED, fd, 0);
	if (data == MAP_FAILED) {
		perror("mmap");
		close(fd);
		return 1;
	}

	for (int i = 0; i < 16; i++) {
		printf("%02hhx ", data[i]);
	}
	printf("\n");

	data[1]++;

	for (int i = 0; i < 16; i++) {
		printf("%02hhx ", data[i]);
	}
	printf("\n");

	close(fd);
	return 0;
}

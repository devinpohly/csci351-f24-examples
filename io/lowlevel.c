#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(void) {
	int f = open("test.txt", O_CREAT | O_RDWR);
	if (f < 0) {
		perror("open");
		return 1;
	}
	int nums[10];
	int bytes = read(f, nums, 10 * sizeof(int));
	if (bytes < 0) {
		perror("read");
		close(f);
		return 1;
	}
	for (int i = 0 ; i < 10; i++) {
		printf("num: %x\n", nums[i]);
	}
	for (int i = 0 ; i < 10; i++) {
		nums[i] = i * i;
	}
	if (lseek(f, 0, SEEK_SET) < 0) {
		perror("lseek");
		close(f);
		return 1;
	}
	int wbytes = write(f, nums, 10 * sizeof(int));
	if (wbytes < 0) {
		perror("write");
		close(f);
		return 1;
	}
	close(f);
	return 0;
}

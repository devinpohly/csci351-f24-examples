#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
	int f = open("test.txt", O_CREAT | O_RDWR);
	int nums[10];
	int bytes = read(f, nums, 10 * sizeof(int));
	for (int i = 0 ; i < 10; i++) {
		printf("num: %x\n", nums[i]);
	}
	/* fscanf(f, "Hello %s", name); */
	/* fprintf(f, "Your name was %s\n", name); */
	close(f);
	return 0;
}

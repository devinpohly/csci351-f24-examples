#include <stdio.h>
#include <unistd.h>

int main(void)
{
	fork();

	if (fork() == 0) {
		return 0;
	}

	fork();

	fork();

	printf("hello\n");
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int somevar;

void *
thread_main(void *varg) {
	int *arg = varg;
	int number = *arg;
	free(varg);

	printf("thread #%d\n", number);
	// Just as an example
	return &somevar;
}

int main(void)
{
	void *retval;
	pthread_t threads[10];
	for (int i = 0; i < 10; i++) {
		int *pi = malloc(sizeof(int));
		*pi = i;
		pthread_create(&threads[i], NULL, thread_main, pi);
	}

	printf("main thread\n");

	for (int i = 0; i < 10; i++) {
		pthread_join(threads[i], &retval);
		/* printf("returned %p (&somevar = %p)\n", retval, &somevar); */
	}
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int somevar;

sem_t semaphore;

void *
thread_main(void *varg) {
	int *arg = varg;
	int number = *arg;
	sem_post(&semaphore);

	printf("thread #%d\n", number);
	// Just as an example
	return &somevar;
}

int main(void)
{
	sem_init(&semaphore, 0, 0);
	void *retval;
	pthread_t threads[10];
	for (int i = 0; i < 10; i++) {
		pthread_create(&threads[i], NULL, thread_main, &i);
		sem_wait(&semaphore);
	}

	printf("main thread\n");

	for (int i = 0; i < 10; i++) {
		pthread_join(threads[i], &retval);
		/* printf("returned %p (&somevar = %p)\n", retval, &somevar); */
	}
	sem_destroy(&semaphore);
	return 0;
}

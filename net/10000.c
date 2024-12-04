#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t lock;

void *plusplus(void *arg) {
	int *px = arg;
	for (int i = 0; i < 1000; i++) {

		// Do lengthy calculation
		usleep(200);

		int calc_result = 1;

		pthread_mutex_lock(&lock);
		*px += calc_result;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main(void) {
	int x = 0;
	int i = 0;

	pthread_mutex_init(&lock, NULL);

	pthread_t threads[10];
	for (i = 0; i < 10; i++) {
		pthread_create(&threads[i], NULL, plusplus, &x);
	}
	for (i = 0; i < 10; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&lock);

	printf("%d\n", x);
	return 0;
}

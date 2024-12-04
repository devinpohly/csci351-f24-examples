#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_ITEMS 20
#define NPROD 3
#define NCONS 5

int queue[MAX_ITEMS];
int head = 0;
int size = 0;

pthread_mutex_t lock;
pthread_cond_t there_is_space;
pthread_cond_t we_have_items;

void produce(int n) {
	pthread_mutex_lock(&lock);
	while (size == MAX_ITEMS) {
		pthread_cond_wait(&there_is_space, &lock);
	}
	int tail = (head + size) % MAX_ITEMS;
	queue[tail] = n;
	size++;
	pthread_cond_signal(&we_have_items);
	pthread_mutex_unlock(&lock);
}

int consume() {
	pthread_mutex_lock(&lock);
	while (size == 0) {
		pthread_cond_wait(&we_have_items, &lock);
	}
	int item = queue[head];
	head++;
	head %= MAX_ITEMS;
	size--;
	pthread_cond_signal(&there_is_space);
	pthread_mutex_unlock(&lock);
	return item;
}

void *producer(void *varg) {
	long start = (long) varg;
	for (int i = 0; i < 1000; i++) {
		produce(start + i);
	}
	return NULL;
}

void *consumer(void *varg) {
	for (;;) {
		int num = consume();
		printf("%d\n", num);
	}
	return NULL;
}

int main(void)
{
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&there_is_space, NULL);
	pthread_cond_init(&we_have_items, NULL);

	pthread_t prods[NPROD], cons[NCONS];
	// Start consumers
	for (int i = 0; i < NCONS; i++) {
		pthread_create(&cons[i], NULL, consumer, NULL);
	}
	// Start producers
	for (int i = 0; i < NPROD; i++) {
		pthread_create(&prods[i], NULL, producer, (void *) (1000L * i));
	}

	// Wait for all producers to finish
	for (int i = 0; i < NPROD; i++) {
		pthread_join(prods[i], NULL);
	}

	// Give the consumers time to finish (HACK - not reliable, don't use
	// sleep as a synchronization construct in practice!)
	sleep(2);

	// Cancel all the consumers
	for (int i = 0; i < NCONS; i++) {
		pthread_cancel(cons[i]);
	}

	pthread_cond_destroy(&we_have_items);
	pthread_cond_destroy(&there_is_space);
	pthread_mutex_destroy(&lock);

	return 0;
}

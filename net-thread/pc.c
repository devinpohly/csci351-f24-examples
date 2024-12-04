#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_ITEMS 20

int queue[MAX_ITEMS];
int head = 0;
int size = 0;

sem_t lock;
sem_t space;
sem_t items;

void produce(int n) {
	sem_wait(&space);
	sem_wait(&lock);
	int tail = (head + size) % MAX_ITEMS;
	queue[tail] = n;
	size++;
	sem_post(&lock);
	sem_post(&items);
}

int consume() {
	sem_wait(&items);
	sem_wait(&lock);
	int item = queue[head];
	head++;
	head %= MAX_ITEMS;
	size--;
	sem_post(&lock);
	sem_post(&space);
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
	sem_init(&lock, 0, 1);
	sem_init(&space, 0, MAX_ITEMS);
	sem_init(&items, 0, 0);

	pthread_t p_thread, c_thread;
	pthread_create(&p_thread, NULL, producer, (void *) 0);
	pthread_create(&p_thread, NULL, producer, (void *) 1000);
	pthread_create(&p_thread, NULL, producer, (void *) 2000);
	pthread_create(&c_thread, NULL, consumer, NULL);
	pthread_create(&c_thread, NULL, consumer, NULL);
	pthread_create(&c_thread, NULL, consumer, NULL);
	pthread_create(&c_thread, NULL, consumer, NULL);
	pthread_create(&c_thread, NULL, consumer, NULL);
	pthread_create(&c_thread, NULL, consumer, NULL);

	pthread_join(p_thread, NULL);
	sleep(2);

	sem_destroy(&items);
	sem_destroy(&space);
	sem_destroy(&lock);

	return 0;
}

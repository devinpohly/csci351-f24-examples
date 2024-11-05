#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int running = 1;

void handle(int signum) {
	printf("nice try. got signal %d\n", signum);
	running = 0;
}

int main(void)
{
	int pid = getpid();
	int ppid = getppid();
	printf("pid %d, parent %d\n", pid, ppid);

	signal(SIGINT, handle);
	//signal(SIGQUIT, handle);
	signal(SIGTERM, handle);
	if (signal(SIGKILL, handle)) {
		perror("handling sigkill");
	}
	while (running) {
		pause();
	}
	printf("clean exit\n");
	return 0;
}

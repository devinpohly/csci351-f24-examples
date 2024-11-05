#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>

int x = 10;

void chld(int sig) {
	printf("got SIGCHLD\n");
}

int main(void) {
	signal(SIGCHLD, chld);

	printf("%d\n", x);
	x = 20;
	printf("%d\n", x);

	for (int i = 0; i < 3; i++) {
		int child_pid = fork();
		if (child_pid == -1) {
			perror("fork");
			exit(1);
		}
		if (child_pid == 0) {
			// this is the child process
			//execvp("sh", (char *[]) {"sh", "-c", "echo $$; sleep 20", NULL});
			execvp("ls", (char *[]) {"ls", "-l", "doesntexist", NULL});
			perror("execvp");
			exit(1);
		}
		// this is the parent process
		printf("parent, child is %d\n", child_pid);

		int status;
		int waited = waitpid(child_pid, &status, WUNTRACED);
		printf("waited = %d\n", waited);
		if (WIFEXITED(status)) {
			printf("exited normally with status %d\n",
					WEXITSTATUS(status));
		} else if (WIFSIGNALED(status)) {
			printf("is swimming with the fishes by signal %d\n", WTERMSIG(status));
		} else if (WIFSTOPPED(status)) {
			printf("paused\n");
		}
	}

	x += 20;
	printf("x_p = %d\n", x);
	sleep(10);
	return 0;
}

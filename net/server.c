#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (lfd < 0) {
		perror("socket");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = htonl(0x0a1651d3);
	inet_aton("10.22.81.211", &addr.sin_addr);
	addr.sin_port = htons(10101);

	int ret = bind(lfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
	if (ret) {
		perror("bind");
		close(lfd);
		return 1;
	}

	ret = listen(lfd, 10);
	if (ret) {
		perror("listen");
		close(lfd);
		return 1;
	}

	// (or)
	// int lfd = open_clientfd("cslab18.wheaton.edu", "10101");

	for (;;) {
		int fd = accept(lfd, NULL, NULL);
		if (fd < 0) {
			perror("accept");
			close(lfd);
			return 1;
		}

		int pid = fork();
		if (pid < 0) {
			perror("fork");
			close(fd);
			close(lfd);
			return 1;
		}
		if (pid > 0) {
			// Parent
			//Put this in a handler for SIGCHLD
			//wait(NULL);
			continue;
		}

		// Child
		close(lfd);
		for (;;) {
			char data[256];

			int b = read(fd, data, 256);
			if (b < 0) {
				perror("read");
				close(fd);
				close(lfd);
				return 1;
			}
			if (b == 0) {
				break;
			}

			data[0] = 'j';
			int wb = write(fd, data, b);
			if (wb < 0) {
				perror("write");
				close(fd);
				close(lfd);
				return 1;
			}
		}

		close(fd);
		return 0;
	}
	close(lfd);
	return 0;
}

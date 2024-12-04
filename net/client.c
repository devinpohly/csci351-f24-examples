#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main(void) {
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 0) {
		perror("socket");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	//addr.sin_addr.s_addr = htonl(0x0a1651d3);
	inet_aton("10.22.81.211", &addr.sin_addr);
	addr.sin_port = htons(10101);

	int ret = connect(fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
	if (ret != 0) {
		perror("connect");
		close(fd);
		return 1;
	}

	// (or)
	// int fd = open_clientfd("cslab18.wheaton.edu", "10101");

	char data[256];
	strcpy(data, "hello world\n");
	int wb = write(fd, data, 12);
	if (wb < 0) {
		perror("write");
		close(fd);
		return 1;
	}


	int b = read(fd, data, 256);
	if (b < 0) {
		perror("read");
		close(fd);
		return 1;
	}
	//fwrite(data, b, 1, stdout);
	wb = write(STDOUT_FILENO, data, b);
	if (wb < 0) {
		perror("write to stdout");
		close(fd);
		return 1;
	}

	close(fd);
	return 0;
}

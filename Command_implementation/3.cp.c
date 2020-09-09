/*************************************************************************
	> File Name: 3.cp.c
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Jul 2020 04:12:03 PM CST
 ************************************************************************/

#include"head.h"

#define MAX_BUFF 1024

int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "Usage : %s file...\n", argv[0]);
		exit(1);
	}
	int fd_in, fd_out;
	if ((fd_in = open(argv[1], O_RDONLY)) == -1) {
		perror("open()");
		exit(1);
	}
	if ((fd_out = creat(argv[2], 0666)) == -1) {
		perror("create()");
		exit(1);
	}
	
	ssize_t nread, nwrite;
	char buff[MAX_BUFF + 5] = {0};
	while ((nread = read(fd_in, buff, MAX_BUFF)) > 0) {
        DBG(GREEN"<Debug>"NONE" : nread = %ld\n strlen(buff) = %ld\n", nread, strlen(buff));
		if ((nwrite = write(fd_out, buff, strlen(buff))) != nread) {
			perror("write()");
		}
		memset(buff, 0, sizeof(buff));
	}

	close(fd_in);
	close(fd_out);
	return 0;
}


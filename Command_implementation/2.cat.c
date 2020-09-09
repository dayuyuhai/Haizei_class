/*************************************************************************
	> File Name: 2.cat.c
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Aug 2020 11:36:02 AM CST
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int n_flag = 0;

void read_file(char *pathname);

int main(int argc, char **argv) {
	if (argc < 2) {
		fprintf(stderr, "Usage : %s[-n] file...\n", argv[0]);
		exit(1);
	}

	int opt;
	while ((opt = getopt(argc, argv, "n")) != -1) {
		switch (opt) {
			case 'n':
				n_flag = 1;
				break;
			default:
				fprintf(stderr, "Usage : %s[-n] file...\n", argv[0]);
				exit(1);
		}
	}

	argc -= optind;
	argv += optind;

	while (argc--) {
		read_file(*argv++);
	}
	return 0;
}


void read_file(char *pathname) {
	FILE *file = NULL;
	char buff[1024] = {0};
	int n = 1;
	if ((file = fopen(pathname, "r")) == NULL) {
		perror("fopen");
		exit(1);
	}
	while (fgets(buff, sizeof(buff), file) != NULL) {
		(n_flag == 1) && printf("%4d  ", n++);
		printf("%s", buff);
		bzero(buff, sizeof(buff));
	}
}


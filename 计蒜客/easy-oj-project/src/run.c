#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "run.h"

void run(const char *program, const char *filein, const char *fileout)
{
	int pid = fork();
	if (pid < 0) {
		return;
	} else if (pid == 0) {
		int fdin = open(filein, O_RDONLY);
		dup2(fdin, 0);
		close(fdin);
		int fdout = open(fileout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fdout, 1);
		close(fdout);
		execlp(program, program, (char *)0);
		exit(1);
	} else {
		waitpid(pid, NULL, 0);
	}
}

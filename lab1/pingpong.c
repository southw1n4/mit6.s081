#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char* argv[])
{
	int p[2];
	char a = 'a';
	char c;
	pipe(p);

	int pid = fork();
	if(pid == 0){
		int pid = getpid();
		read(p[0], &c, 1);
		fprintf(2, "%d: received ping\n", pid);
		write(p[1], &a, 1);

		close(p[0]);
		close(p[1]);
		exit(0);
	
	}else {
		int pid = getpid();
		write(p[1], &a, 1);

		wait(0);
		read(p[0], &c, 1);
		fprintf(2, "%d: received pong\n", pid);

		close(p[0]);
		close(p[1]);

	}

	exit(0);
}

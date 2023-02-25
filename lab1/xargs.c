#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

#define MAX_LINE_SIZE 512
int
getline(char* buf)
{
	int n = 0;
	while(read(0, &buf[n], 1) != 0){
		if(buf[n] == '\n') break;
		++ n;
	}
	buf[n] = 0;
	
	return n;
}

void
run(char* cmd, char** argv)
{
	int pid = fork();
	if(pid == 0){
		exec(cmd, argv);
		exit(0);
	}else 
		return ;
}



int 
main(int argc, char* argv[]) 
{
	if(argc < 3){
		fprintf(2, "Usage: xargs <command>\n");
		exit(-1);
	}
	
	char* p[MAXARG];
	int n = 0;
	for(; n + 1 < argc; ++ n){
		p[n] = argv[n + 1];
	}

	char buf[MAX_LINE_SIZE];
	p[n] = buf;
	while(getline(buf) != 0) {
		run(argv[1], p);
	}
	wait(0);

	exit(0);
}

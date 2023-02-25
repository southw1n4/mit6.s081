#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void
is_prime(int num) 
{
	int flag = 1;	
	for(int i = 2; i < num; ++ i){
		if(num % i == 0){
			flag = 0;
			break;
		}
	}

	if(flag) fprintf(1, "prime %d\n", num);
	
	return ;
}

int
main(int argc, char* argv[]) 
{
	int p[2];
	pipe(p);

	int pid = fork();
	if(pid != 0){
		for(int i = 2; i <= 35; ++ i){
			write(p[1], &i, 4);
		}

		close(p[0]);
		close(p[1]);

		wait(0);
	
	}else {
		int num;
		while(read(p[0], &num, 4) != 0) {
			int sp[2];
			pipe(sp);

			int spid = fork();
			if(spid != 0){
				write(sp[1], &num, 4);

				close(sp[1]);
				close(sp[0]);
			}else {
				int t;
				read(sp[0], &t, 4);
				
				is_prime(t);
				
				close(sp[0]);
				close(sp[1]);
				
				exit(0);
			}
		}

		close(p[0]);
		close(p[1]);
		wait(0);

		exit(0);
		
	}

	exit(0);

}

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


int
main(int argc, char* argv[])
{
	if(argc < 2){
		fprintf(2, "Usage: sleep time\n");
		exit(1);
	}

	int sleep_time = atoi(argv[1]);
	if(sleep_time < 0){
		fprintf(2, "time must be positive\n");
		exit(1);
	}
	
        fprintf(2, "Nothing happen for a little while\n");
	sleep(sleep_time);

	exit(0);
}


#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

const char* SELF = ".";
const char* PARENT = "..";
const char* NEXT_LINE = "\n";

void
find(const char* path, const char* target)
{
	int fd;
	if((fd = open(path, 0)) < 0) {
		fprintf(2, "Cannot open dir: %s\n", path);
		return ;
	}


	struct stat st;
	if(fstat(fd, &st) < 0 || st.type != T_DIR){
		return ;
	}

	char buf[512];
	char *p;
	struct dirent de;

	strcpy(buf, path);
	p = buf + strlen(buf);
	*p++ = '/';
	while(read(fd, &de, sizeof (de)) == sizeof (de)){
		if(strcmp(de.name, SELF) == 0 ||
		   strcmp(de.name, PARENT) == 0 ||
		   de.inum == 0 )
		   	continue;

		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		if(stat(buf, &st) < 0) {
			return ;
		}

		switch(st.type) {
		case T_DEVICE:
		case T_FILE:
			if(strcmp(de.name, target) == 0 ){
			//	fprintf(2, "%s\n", buf);
				write(1, buf, strlen(buf));
				write(1, NEXT_LINE, 1);
			}
			break;
		case T_DIR:
			find(buf, target);
			break;
		}

	}


}

int
main(int argc, char* argv[])
{
	if(argc < 3){
		fprintf(2, "Usage: find <dir> <filename>\n");
		exit(1);
	}

	char* target = argv[2];
	char* src = argv[1]; 

	find(src, target);

	exit(0);
}



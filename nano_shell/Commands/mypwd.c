#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mypwd.h"

#define BUF_SIZE   1024
int runMypwd() {

	char buf[BUF_SIZE];
	if (getcwd(buf, sizeof(buf)) != NULL) {
		printf("%s\n", buf);
	}else {
       		perror("Failure getting current working directory!");
		return -1;
	}

	return 0;	
}

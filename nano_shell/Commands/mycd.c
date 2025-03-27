#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "mycd.h"

int runMycd (int argc, char **argv) {

    // If no argument is provided, change to home directory
    if (argc == 1) {
        char *home = getenv("HOME");
        if (home == NULL) {
            fprintf(stderr, "cd: HOME environment variable not set\n");
	    return -1;
        }
        if (chdir(home) != 0) {
            perror("cd");
	    return -1;
        }	
	return 0;
    }

    // Normal directory change
    if (chdir(argv[1]) != 0) {
        perror("cd");
	return 0;
    }

}

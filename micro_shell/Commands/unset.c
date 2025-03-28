#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Program/program.h"

int runMyunset(int argc, char* argv[]) {
	if (argc < 2) {
        	perror("Usage: unset VARIABLE [VARIABLE...]");
        	return -1;
    	}

	for (int i = 1; i < argc; ++i) {
		char* variable = argv[i];
	       // Check if is is an enviroment variable
    		if (getenv(variable) != NULL) {
    			if (unsetenv(variable) != 0) {
        			perror("unset failed");
				return -1;
    			}
		} else {
			// Check if it is a local variable
			if (unset_local_var(argv[i]) == -1) {
				perror("unset local variable failed");
				return -1;
			}
		}
	}
	return 0;
}

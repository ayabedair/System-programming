#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int runMyexport(int argc, char *argv[])
{
    // print all, if no argument was passed
    if (argc == 1) {
	extern char **environ;
	for (char **env = environ; *env; env++) {
	    printf("%s\n", *env);
	}
	return 0;
    }

    for (int i = 1; i < argc; ++i) {
	char* variable = argv[i];
	// Check if the input contains an '=' sign
	char *equal = strchr(variable, '=');

	if (equal == NULL) {
	    if (setenv(variable, "", 0) != 0) {
		perror("export failed");
		return -1;
	    }
	} else {
	    // Split into name and value
	    *equal = '\0';
	    char *name = variable;
	    char *value = equal + 1;

	    // Set the environment variable
	    if (setenv(name, value, 1) != 0) {
		perror("export failed");
		return -1;
	    }

	    // Restore the '=' sign (optional, as we might not need the original string)
	    *equal = '=';
	}
    }
    return 0;

}

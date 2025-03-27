#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Program/program.h"
#include "App/app.h"
//extern char **environ;

int main() {
	char *command = NULL;
	size_t size = 0;
	while(true) {
		// print prompet
		print_prompet();

		// Read input
		ssize_t char_read = getline(&command, &size, stdin);

		if (char_read == 1) {
			continue;
		}

		// remove new line
		command[char_read - 1] = '\0';

		// terminate if exit was called
		if (strcmp(command, "exit") == 0) {
			free(command);
			break;
		}

		// parse command
		int argc;
		char **argv = parse_command(command, &argc);

		if (argv != NULL) {
			if (!execute_command(argc, argv)) {
				int status;
				pid_t pid = fork();

				if (pid > 0) {
		                	wait(&status);	
				} else if (pid == 0) {
					execvp(argv[0], argv);
					perror("Invalid Command");
					exit(EXIT_FAILURE);
				} else {
					perror("fork failed");
					exit(EXIT_FAILURE);
				}
			}
		}

		free_command_args(argv);
	}
	return 0;
}

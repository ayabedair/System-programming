#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "../Commands/myecho.h"
#include "../Commands/mypwd.h"
#include "../Commands/mycd.h"

#define MAX_ARGS 64 

char **parse_command(const char *command, int *argc) {
    if (command == NULL || argc == NULL) {
        return NULL;
    }

    char **argv = malloc(MAX_ARGS * sizeof(char*));
    if (argv == NULL) {
        perror("parse_command: malloc failed");
        return NULL;
    }

    char *cmd_copy = strdup(command);
    if (cmd_copy == NULL) {
        perror("strdup failed");
        free(argv);
        return NULL;
    }

    *argc = 0;
    char *token = strtok(cmd_copy, " ");

    while (token != NULL && *argc < MAX_ARGS - 1) {
        // Skip empty tokens (from multiple spaces)
        if (*token != '\0') {
            argv[*argc] = strdup(token);
            if (argv[*argc] == NULL) {
                perror("parse_command: strdup failed");

                // free allocated memory
                for (int i = 0; i < *argc; i++) {
                    free(argv[i]);
                }
                free(argv);
                free(cmd_copy);

                return NULL;
            }
            (*argc)++;
        }
        token = strtok(NULL, " ");
    }

    argv[*argc] = NULL;
    free(cmd_copy);
    return argv;
}

void free_command_args(char **argv) {
    if (argv == NULL) return;

    for (int i = 0; argv[i] != NULL; i++) {
        free(argv[i]);
    }
    free(argv);
}

bool execute_command(int argc, char* argv[]) {
	if (strcmp(argv[0], "echo") == 0) {
		if (runMyecho(argc, argv) == -1) {
			perror("echo: failed");
			return false;
		}
	} else if (strcmp(argv[0] ,"pwd") == 0) {
		if (runMypwd(argc, argv) == -1) {
			perror("pwd: failed");
			return false;
		}
	} else if (strcmp(argv[0] ,"cd") == 0) {
		if (runMycd(argc, argv) == -1) {
			perror("cd: failed");
			return false;
		}
	} else {
		return false;
	}
	return true;
}

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "../Commands/myecho.h"
#include "../Commands/mypwd.h"
#include "../Commands/mycd.h"
#include "../Commands/export.h"
#include "../Commands/unset.h"

#define MAX_ARGS 64 
#define MAX_SIZE 64

typedef struct Variable {
    char varName[50];
    char varValue[50];
    struct Variable *next;
} Variable;

Variable *head = NULL;

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

bool is_var(char* argv, char* name, char* val) {
	for (int i = 1; argv[i]; i++) {
	       if (argv[i] == '=') {
		       strncpy(name, argv, i);
            	       name[i] = '\0';
                       strcpy(val, argv + i + 1);
	       	       return true;
	       }
	}
	return false;
}	


bool store_local_var(char* varName, char* varVal) {
	// Overwrite the value, if the variable was stored previously
	Variable *current = head;
    	while (current != NULL) {
        	if (strcmp(current->varName, varName) == 0) {
			strcpy(current->varValue, varVal);
            		return true;
        	}
        	current = current->next;
    	}
    
	// Create new variable	
	Variable *newVar = (Variable *)malloc(sizeof(Variable));
	if (newVar != NULL) {
        	strcpy(newVar->varName, varName);
        	strcpy(newVar->varValue, varVal);
        	newVar->next = head;
        	head = newVar;
		return true;
	} else {
		perror("store_local_var: failed to allocate new memory"); 
		return false;
	}

	return false;
}

void replace_var(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '$') {
	    	char* name = argv[i] + 1;

   		// Search in enviroment variables
		char* env_value = getenv(name);
            	if (env_value != NULL) {
                	char* new_value = strdup(env_value);
                	free(argv[i]);
                	argv[i] = new_value;
                	return;
            	}
	
		// Search in local variables
            Variable *current = head;
            
            while (current != NULL) {
                if (strcmp(current->varName, name) == 0) {
                    char* new_value = strdup(current->varValue);
                    free(argv[i]);
                    argv[i] = new_value;
                    return;
                }
                current = current->next;
            }
            
            // if variable not found - replace with empty string
            free(argv[i]);
            argv[i] = strdup("");
            return;
        }
    }
}

int unset_local_var(char* name) {
	Variable *current = head;
	Variable *previous = NULL;
        while (current != NULL) {
                if (strcmp(current->varName, name) == 0) {
                        if (previous == NULL) {
                		// Deleting the head node
                		head = current->next;
            		} else {
                		// Deleting a middle or tail node
                		previous->next = current->next;
            		}
            		free(current);
            		return 0;
                }
		previous = current;
        	current = current->next;
        }
	return -1;
}


bool execute_command(int argc, char* argv[]) {
	// Check for Local variables
	char* varName = (char*) malloc(MAX_SIZE * sizeof(char));
    	char* varVal = (char*) malloc(MAX_SIZE * sizeof(char));
	if (argc == 1 && is_var(argv[0], varName, varVal)) {
		if (store_local_var(varName, varVal)) return true;
		else return false;
	}

	// Replace var if $ sign was found
	replace_var(argc, argv);
	

	// Check for built-in commands
	if (strcmp(argv[0], "export") == 0) {
		if (runMyexport(argc, argv) == -1) {
			perror("export: failed");
			return false;
		}
	} else if (strcmp(argv[0], "unset") == 0) {
		if (runMyunset(argc, argv) == -1) {
			perror("unset: failed");
			return false;
		}
	} else if (strcmp(argv[0], "echo") == 0) {
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

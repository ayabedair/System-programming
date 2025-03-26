#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define MAX_INPUT 1000000

int main() {
	char input[MAX_INPUT];

	while (true) {
		printf("My Femto shell> ");
		fflush(stdout);

		// Read input
		if (fgets(input, MAX_INPUT, stdin) == NULL) {
			break;	
		}
		

		// remove newline from input
		input[strcspn(input, "\n")] = '\0';


		// no input
		if (*input == '\0') {
			continue;
		}

		// calling echo with arguments
		if (strncmp(input, "echo ", 5) == 0) {
        		printf("%s\n", input + 5);
    		}
		// calling echo without arguments
		else if (strcmp(input, "echo") == 0) {
			printf("\n");
		}
		// calling exit
		else if (strcmp(input, "exit") == 0) {
        		printf("Good Bye\n");
        		exit(0);
    		}
		// Invalid command
		else {
        		printf("Invalid command\n");
    		}
	}

	return 0;
}

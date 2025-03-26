#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void main(int argc, char *argv[]) {
	int new_line = 1;

        if (argc > 1 && strcmp(argv[1], "-n") == 0) {
                new_line = 0;
                argv++;
                argc--;
        }

        for (int i = 1; i < argc; i++) {
		if(write(STDOUT_FILENO, argv[i], strlen(argv[i])) == -1) {
				perror("Failed to write");
				exit(EXIT_FAILURE);
		}

                if(i != argc - 1) {
                        write(STDOUT_FILENO, " ", 1);
		}
        }

        if (new_line) {
                printf("\n");
	}
}

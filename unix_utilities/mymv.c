#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {

	if (argc != 3) {
		perror("Usage: mymv <file> <new_name / new_destination>");
		exit(EXIT_FAILURE);
	}

	if (rename(argv[1], argv[2]) != 0) {
		perror("Failed to rename file");
		exit(EXIT_FAILURE);
	}

	return 0;
}

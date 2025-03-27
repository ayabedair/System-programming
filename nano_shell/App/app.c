#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#define MAX_SIZE  1024
#define BOLD_MAGENTA   "\x1b[35m\x1b[1m"
#define BOLD_YELLOW     "\x1b[33m\x1b[1m"
#define COLOR_RESET     "\x1b[0m"

void print_prompet()
{
	// Get user name
	char *userName = getlogin();
	if (userName == NULL) {
		perror("app.c: void print_prompet() failed");
		exit(EXIT_FAILURE);
	}
	// Get host name
	char hostName[MAX_SIZE];
	if (gethostname(hostName, sizeof(hostName)) == -1) {
		perror("app.c: void print_prompet() failed");
		exit(EXIT_FAILURE);
	}
	// Get current working directory
	char cwd[MAX_SIZE];
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		perror("getcwd error");
		exit(EXIT_FAILURE);
	}
	// Print the prompt
	printf(BOLD_YELLOW "%s@%s" BOLD_MAGENTA ":%s" COLOR_RESET "> ",
	       userName, hostName, cwd);
}

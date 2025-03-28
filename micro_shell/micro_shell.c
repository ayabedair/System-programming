#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Program/program.h"
#include "App/app.h"
#include "Redirection/redirection.h"


int main() {
    char *command = NULL;
    size_t size = 0;
    int saved_stdout = dup(STDOUT_FILENO); // Save original stdout
    int saved_stdin = dup(STDIN_FILENO); // Save original stdout
    int saved_stderr = dup(STDERR_FILENO); // Save original stdout

    while (true) {
        print_prompet();
        ssize_t char_read = getline(&command, &size, stdin);

        if (char_read == 1) continue; // Empty input
        command[char_read - 1] = '\0'; // Remove newline

        if (strcmp(command, "exit") == 0) {
            free(command);
            break;
        }

        int argc;
        char **argv = parse_command(command, &argc);
        if (!argv) continue;

        // Handle output redirection (modifies argv/argc)
        char *output_file = NULL;
        int append = 0;
        if (parse_output_redirection(argv, &argc, &output_file, &append)) {
            redirect_output(output_file, &saved_stdout, append);
        }

	// Handle input redirection (modifies argv/argc)
        char *input_file = NULL;
        if (parse_input_redirection(argv, &argc, &input_file)) {
            redirect_input(input_file, &saved_stdin);
        }

	// Handle error redirection (modifies argv/argc)
        char *error_file = NULL;
        if (parse_error_redirection(argv, &argc, &error_file, &append)) {
            redirect_output(error_file, &saved_stderr, append);
        }

        // Try built-ins (no fork needed)
        bool handled = execute_command(argc, argv);
        
        if (!handled) {
            // External command: fork and exec
            pid_t pid = fork();
            if (pid == 0) { // Child
                execvp(argv[0], argv);
                perror("execvp failed");
                dup2(saved_stdout, STDOUT_FILENO); // Restore stdout before exit
                dup2(saved_stdin, STDIN_FILENO); // Restore stdin before exit
                dup2(saved_stderr, STDERR_FILENO); // Restore stderr before exit
                exit(EXIT_FAILURE);
            } 
            else if (pid > 0) { // Parent
                wait(NULL); // Wait for child
            } 
            else {
                perror("fork failed");
            }
        }

        // Restore stdout if redirection happened
        if (output_file) {
            dup2(saved_stdout, STDOUT_FILENO);
        }
	// Restore stdin if redirection happened
        if (input_file) {
            dup2(saved_stdin, STDIN_FILENO);
        }
	// Restore stderr if redirection happened
        if (error_file) {
            dup2(saved_stderr, STDERR_FILENO);
        }

        free_command_args(argv);
    }

    close(saved_stdout);
    return 0;
}

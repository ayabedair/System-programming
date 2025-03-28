#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int parse_output_redirection(char **argv, int *argc, char **output_file, int *append) {
    *output_file = NULL;
    *append = 0;  // Default: overwrite mode
    int i = 0;
    
    while (argv[i] != NULL) {
        // Case 1: Standalone ">" or ">>"
        if (strcmp(argv[i], ">") == 0 || strcmp(argv[i], ">>") == 0) {
            *append = (strcmp(argv[i], ">>") == 0) ? 1 : 0;
            free(argv[i]);  // Free the ">" or ">>" token
            if (argv[i+1] != NULL) {
                *output_file = argv[i+1];
                argv[i] = NULL;
                *argc = i;
                return 1;
            }
        }
        // Case 2: ">out.txt" or ">>out.txt" (no space)
        else if ((argv[i][0] == '>' && strlen(argv[i]) > 1) && 
                 (argv[i][1] != '>' && argv[i][1] != '2')) {  // Ensure not ">>" or "2>"
            *append = (argv[i][1] == '>') ? 1 : 0;
            *output_file = argv[i] + 1 + (*append);  // Skip '>' or '>>'
            free(argv[i]);
            argv[i] = NULL;
            *argc = i;
            return 1;
        }
        // Case 3: "file.txt>out.txt" or "file.txt>>out.txt" (embedded '>')
        else {
            char *redirect_pos = strchr(argv[i], '>');
            if (redirect_pos != NULL && 
                (redirect_pos == argv[i] || *(redirect_pos - 1) != '2')) {  // Not "2>"
                *append = (*(redirect_pos + 1) == '>') ? 1 : 0;  // Check for ">>"
                *redirect_pos = '\0';  // Split the string
                *output_file = redirect_pos + 1 + (*append);  // Skip '>' or '>>'
                *argc = i + 1;
                return 1;
            }
        }
        i++;
    }
    *argc = i;
    return 0;
}


int redirect_output(char* output_file, int* saved_stdout, int append) {
    // Save original stdout
    *saved_stdout = dup(STDOUT_FILENO);
    if (*saved_stdout == -1) {  // Fixed: Dereference the pointer
        perror("dup");
        return -1;  // Return error instead of exit()
    }

    // Open the output file with correct flags
    int flags = O_WRONLY | O_CREAT;
    flags |= append ? O_APPEND : O_TRUNC;  // Use append flag if specified
    int fd = open(output_file, flags, 0644);
    if (fd == -1) {
        perror("open");
        close(*saved_stdout);  // Clean up saved fd
        return -1;
    }

    // Redirect stdout to the file
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        close(fd);
        close(*saved_stdout);
        return -1;
    }
    close(fd);
    return 0;  // Success
}

int parse_input_redirection(char **argv, int *argc, char **input_file) {
    *input_file = NULL;
    int i = 0;

    while (argv[i] != NULL) {
        // Case 1: Standalone "<"
        if (strcmp(argv[i], "<") == 0) {
            free(argv[i]);
            if (argv[i+1] != NULL) {
                *input_file = argv[i+1];
                argv[i] = NULL;
                *argc = i;
                return 1;
            }
        }
        // Case 2: "<input.txt" (no space)
        else if (argv[i][0] == '<' && strlen(argv[i]) > 1) {
            *input_file = argv[i] + 1;  // Skip '<'
            free(argv[i]);
            argv[i] = NULL;
            *argc = i;
            return 1;
        }
        // Case 3: "command<input.txt" (embedded '<')
        else {
            char *redirect_pos = strchr(argv[i], '<');
            if (redirect_pos != NULL) {
                *redirect_pos = '\0';  // Split the string
                *input_file = redirect_pos + 1;
                *argc = i + 1;
                return 1;
            }
        }
        i++;
    }
    *argc = i;
    return 0;
}

int redirect_input(char* input_file, int* saved_stdin) {
    // Save original stdin
    *saved_stdin = dup(STDIN_FILENO);
    if (*saved_stdin == -1) {
        perror("dup");
        return -1;
    }

    // Open the input file
    int fd = open(input_file, O_RDONLY);
    if (fd == -1) {
        perror("open");
//        close(*saved_stdin);
        return -1;
    }

    // Redirect stdin to the file
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd);
        close(*saved_stdin);
        return -1;
    }
    close(fd);
    return 0;
}

int parse_error_redirection(char **argv, int *argc, char **error_file, int *append) {
    *error_file = NULL;
    *append = 0;
    int i = 0;

    while (argv[i] != NULL) {
        // Case 1: Standalone "2>" or "2>>"
        if (strncmp(argv[i], "2>", 2) == 0) {
            *append = (strlen(argv[i]) > 2 && argv[i][2] == '>') ? 1 : 0;
            free(argv[i]);
            if (argv[i+1] != NULL) {
                *error_file = argv[i+1];
                argv[i] = NULL;
                *argc = i;
                return 1;
            }
        }
        // Case 2: Embedded "2>" or "2>>"
        else {
            char *redirect_pos = strstr(argv[i], "2>");
            if (redirect_pos != NULL) {
                *append = (*(redirect_pos + 2) == '>') ? 1 : 0;
                *redirect_pos = '\0';
                *error_file = redirect_pos + 2 + (*append);
                *argc = i + 1;
                return 1;
            }
        }
        i++;
    }
    *argc = i;
    return 0;
}

int redirect_error(char* error_file, int* saved_stderr, int append) {
    // Save original stderr
    *saved_stderr = dup(STDERR_FILENO);
    if (*saved_stderr == -1) {
        perror("dup");
        return -1;
    }

    // Open the error file
    int flags = O_WRONLY | O_CREAT;
    flags |= append ? O_APPEND : O_TRUNC;
    int fd = open(error_file, flags, 0644);
    if (fd == -1) {
        perror("open");
        close(*saved_stderr);
        return -1;
    }

    // Redirect stderr to the file
    if (dup2(fd, STDERR_FILENO) == -1) {
        perror("dup2");
        close(fd);
        close(*saved_stderr);
        return -1;
    }
    close(fd);
    return 0;
}

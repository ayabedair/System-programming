#ifndef REDIRECTION_H
#define REDIRECTION_H	

int parse_output_redirection(char **argv, int *argc, char **output_file, int *append);
int redirect_output(char* output_file, int* saved_stdout, int append);

int parse_input_redirection(char **argv, int *argc, char **input_file);
int redirect_input(char* input_file, int* saved_stdin);

int parse_error_redirection(char **argv, int *argc, char **error_file, int *append);
int redirect_error(char* error_file, int* saved_stderr, int append);
#endif

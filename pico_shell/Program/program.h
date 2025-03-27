#ifndef HANDLENING_COMMANDS_H
#define HANDLENING_COMMANDS_H

#include <stdbool.h>

char **parse_command(const char *command, int *argc);
void free_command_args(char **argv);
bool execute_command(int argc, char* argv[]);

#endif

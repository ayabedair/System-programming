# Pico Shell - README
![C Programming](https://img.shields.io/badge/Language-C-blue)
![License](https://img.shields.io/badge/License-MIT-green)

## Overview
Pico Shell is a simple Unix shell implemented in C that supports basic shell functionalities. It provides built-in commands (`echo`, `pwd`, `cd`, `exit`), and for other commands, it uses `fork` and `exec` system calls to execute external programs. The shell processes commands entered by the user, parses the command line into arguments, and manages memory dynamically to support any number of arguments.

## Features
1. **Built-in Commands**:
   - **echo**: Prints the arguments to the standard output.
   - **pwd**: Prints the current working directory.
   - **cd**: Changes the current directory.
   - **exit**: Exits the shell.

2. **Command Line Parsing**:
   - The shell parses user input, splitting the command and its arguments based on spaces (supports multiple spaces).
   
3. **Executing External Programs**:
   - Any command other than the built-in commands is executed by the shell using `fork` and `exec` system calls.
   - The shell supports executing programs by their names without needing to provide the full path (e.g., `ls` instead of `/bin/ls`).

## Compilation
To compile the Pico Shell program, run the following command in your terminal:

```bash
# Clone repository
git clone https://github.com/ayabedair/system-programming.git
cd system-programming/pico_shell

# Build
gcc pico_shell.c Program/*.c Commands/*.c App/*.c -o pico_shell


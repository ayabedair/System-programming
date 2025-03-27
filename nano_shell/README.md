# Nano Shell - README
![C Programming](https://img.shields.io/badge/Language-C-blue)
![License](https://img.shields.io/badge/License-MIT-green)

## Overview
This is an updated virsion of My pico shell, the updates:
  - Saving Local Variables: using a linked-list
  - Export Command: New export built-in to promote variables to environment
  - Environment Inheritance: Child processes inherit the shell's full environment
  - Unset Command: New unset built-in to remove enviroment and local variables
  - Variable Substitution: Supports $VAR syntax expansion in commands

## Features
1. **Built-in Commands**:
   - **export**:
       - Without arguments: Lists all exported variables
       - With VAR: Promotes a shell variable to an environment variable
   - **unset**: Removes a shell or environment variable
   - **echo**: Prints the arguments to the standard output.
   - **pwd**: Prints the current working directory.
   - **cd**: Changes the current directory.
   - **exit**: Exits the shell.
    

3. **Command Line Parsing**:
   - The shell parses user input, splitting the command and its arguments based on spaces (supports multiple spaces).
   
4. **Executing External Programs**:
   - Any command other than the built-in commands is executed by the shell using `fork` and `exec` system calls.
   - The shell supports executing programs by their names without needing to provide the full path (e.g., `ls` instead of `/bin/ls`).

## Compilation
To compile the Pico Shell program, run the following command in your terminal:

```bash
# Clone repository
git clone https://github.com/ayabedair/system-programming.git
cd system-programming/nano_shell

# Build
gcc nano_shell.c Program/*.c Commands/*.c App/*.c -o nano_shell
```

# Femto Shell 

![C](https://img.shields.io/badge/Language-C-blue)
![License](https://img.shields.io/badge/License-MIT-green)

A minimal shell that supports the following built in commands:

- echo: echoes any text entered by the user.

- exit: If the user entered "exit", the shell will reply with "Good Bye" and terminate.

- print an "Invalid command" error if the user entered any command other than "echo" and "exit".

## Features

- Simple command prompt interface
- Built-in `echo` command with/without arguments
- `exit` command to terminate the shell
- Input buffer handling (up to 1MB)
- Basic error handling for invalid commands

## Compilation
```bash
gcc femto_shell.c -o femto_shell
```

## Usage
![image](https://github.com/user-attachments/assets/ffaba1b2-7a94-45e8-b451-56ea010a178c)

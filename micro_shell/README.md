# MicroShell - README
![C Programming](https://img.shields.io/badge/Language-C-blue)
![License](https://img.shields.io/badge/License-MIT-green)

# Overview
This is an updated virsion of My Femto shell, the updates:
  - Handling redirection of input/output/error
  - Redirection of output/error can be done in append mode

# Features
## 1️⃣ Redirection Support

#### 1. Output Redirection
| Syntax       | Description                | Example                 |
|--------------|----------------------------|-------------------------|
| `>`          | Overwrite file             | `ls > output.txt`       |
| `>>`         | Append to file             | `date >> log.txt`       |
| `cmd>file`   | No-space syntax            | `echo hello>greeting`   |
| `cmd arg>f`  | With arguments             | `grep err log>errors`   |

#### 2. Input Redirection
| Syntax       | Description                | Example                 |
|--------------|----------------------------|-------------------------|
| `<`          | Read from file             | `sort < data.txt`       |
| `cmd<file`   | No-space syntax            | `wc -l<notes.txt`       |

#### 3. Error Redirection
| Syntax       | Description                | Example                 |
|--------------|----------------------------|-------------------------|
| `2>`         | Redirect stderr            | `cmd 2> errors.log`     |
| `2>>`        | Append stderr              | `cmd 2>>debug.log`      |
| `cmd 2>err`  | With arguments             | `make 2>build_errors`   |

## 2️⃣ Built-in Commands

| Command | Description                     | Example                   |
|---------|---------------------------------|---------------------------|
| `cd`    | Change directory               | `cd /home`           |
| `pwd`   | Print working directory        | `pwd`                     |
| `echo`  | Display message                | `echo "Hello $USER"`      |
| `export`| Set environment variable       | `export PATH=$PATH:/bin`  |
| `unset` | Remove variable                | `unset TEMP_DIR`          |
| `exit`  | Quit the shell                 | `exit`                    |

## 3️⃣ Variable Handling

#### 1. Set Local Variables
```bash
# Set and use local variable
$ NAME="MicroShell"
$ echo "Hello $NAME"
Hello MicroShell

# Multi-word values
$ DEST="/home"
$ ls $DEST
list of files/directories in /home
```
#### 2. Set Environment Variables
```bash
# Set environment variable
$ export PATH="$PATH:/custom/bin"
$ echo $PATH
/usr/bin:/bin:/custom/bin
```
#### 3. Unsetting Variables
```bash
$ TEMP="data"
$ export GLOB="to be removed"
$ unset TEMP
$ unset GLOB
$ echo $TEMP $GLOB
[empty output]
```

## 4️⃣ Command Execution Without Full Paths
```bash
$ ls
$ touch file.txt
# and all other commands
```
# Compilation
To compile the Micro Shell program, run the following command in your terminal:

```bash
# Clone repository
git clone https://github.com/ayabedair/system-programming.git
cd system-programming/micro_shell

# Build
gcc micro_shell.c Redirection/*.c Program/*.c App/*.c Commands/*.c -o micro_shell
```

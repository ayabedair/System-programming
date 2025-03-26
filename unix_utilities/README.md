# Unix Utilities

![C Programming](https://img.shields.io/badge/Language-C-blue)
![License](https://img.shields.io/badge/License-MIT-green)

A collection of minimal Unix command-line utilities implemented in C as part of system programming studies.

## Included Utilities

| Utility | Description | Implementation File |
|---------|-------------|---------------------|
| `mymv`  | File mover/renamer | [mymv.c](./mymv.c) |
| `mycp`  | File copier | [mycp.c](mycp.c) |
| `myecho`| Argument echo | [myecho.c](myecho.c) |
| `mypwd` | Working directory printer | [mypwd.c](mypwd.c) |

## Build & Install

### Prerequisites
- GCC compiler

### Compilation
```bash
# Clone repository
git clone https://github.com/ayabedair/system-programming.git
cd system-programming/unix_utilities

# Build all utilities
gcc mymv.c -o mymv
gcc mycp.c -o mycp
gcc myecho.c -o myecho
gcc mypwd.c -o mypwd
```
## Usage
### mymv
```bash
# Rename a file
./mymv oldname.txt newname.txt

# Move file to different directory
./mymv document.pdf ~/Documents/
```
### mycp
```bash
# Create copy in same directory
./mycp original.txt backup.txt

# Copy to another directory
./mycp image.jpg /var/www/uploads/
```

### myecho
```bash
# Simple message
./myecho "System Programming"

# Multiple arguments
./myecho CPU: $(grep -c processor /proc/cpuinfo)

# No newline (-n flag)
./myecho -n "Loading... "
```
### mypwd
```bash
# Print working directory
./mypwd
```

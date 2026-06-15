# 📁 File Manager in C

A lightweight, command-line file management tool written in C. Supports listing, copying, moving, deleting, searching, and inspecting files and directories — with colored terminal output.

## Features

- 📂 List directory contents with optional hidden files and detailed view
- ➕ Create and recursively remove directories
- 📋 Copy and move files (cross-device supported)
- 🗑️ Delete files with confirmation prompt
- ✏️ Rename files and directories
- 🔍 Search files with wildcard patterns (e.g. `*.c`, `report*`)
- ℹ️ Detailed file/directory info (size, permissions, timestamps, inode)
- 🎨 ANSI colored output for better readability

## Build

```bash
git clone https://github.com/pronabcoding/File-Manager-in-C
cd file-manager-c
make
```

Requires GCC and a POSIX-compatible OS (Linux / macOS).

## Usage

```
./file_manager <command> [args...]
```

| Command | Arguments | Description |
|---------|-----------|-------------|
| `ls` | `<path> [-a] [-l]` | List directory (`-a` hidden, `-l` details) |
| `mkdir` | `<path>` | Create a directory |
| `rmdir` | `<path>` | Remove directory recursively |
| `cp` | `<src> <dest>` | Copy a file |
| `mv` | `<src> <dest>` | Move a file |
| `rm` | `<path>` | Delete a file |
| `rn` | `<old> <new>` | Rename a file |
| `info` | `<path>` | Show file/directory info |
| `find` | `<dir> <pattern>` | Search with wildcard |
| `help` | | Show help |

## Examples

```bash
# List current directory with details
./file_manager ls . -l

# List including hidden files
./file_manager ls /home/user -a -l

# Copy a file
./file_manager cp report.txt backup/report.txt

# Search for all C source files
./file_manager find . "*.c"

# Get info on a directory
./file_manager info /var/log

# Rename a file
./file_manager rn old_name.txt new_name.txt
```

## Project Structure

```
file-manager/
├── include/
│   └── file_manager.h     # Header: structs, constants, declarations
├── src/
│   ├── main.c             # Entry point & CLI parsing
│   ├── directory.c        # Directory operations & search
│   ├── file_ops.c         # File copy/move/delete/info
│   └── utils.c            # Helpers: size, permissions, banner
├── Makefile
└── README.md
```

## Cleaning Up

```bash
make clean
```

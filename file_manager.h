#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

#define MAX_PATH 1024
#define MAX_NAME 256
#define VERSION  "1.0.0"

/* ANSI color codes */
#define COLOR_RESET   "\033[0m"
#define COLOR_BOLD    "\033[1m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_CYAN    "\033[36m"

typedef struct {
    char name[MAX_NAME];
    char path[MAX_PATH];
    off_t size;
    time_t modified;
    int is_dir;
    mode_t permissions;
} FileInfo;

/* directory operations */
void list_directory(const char *path, int show_hidden, int show_details);
int  create_directory(const char *path);
int  remove_directory(const char *path);

/* file operations */
int  copy_file(const char *src, const char *dest);
int  move_file(const char *src, const char *dest);
int  delete_file(const char *path);
int  rename_file(const char *old_path, const char *new_path);

/* search & info */
void search_files(const char *dir, const char *pattern);
void file_info(const char *path);
long get_dir_size(const char *path);

/* utilities */
void print_size(long bytes);
void print_permissions(mode_t mode);
void print_banner(void);
void print_help(void);

#endif /* FILE_MANAGER_H */

#include "../include/file_manager.h"
#include <fnmatch.h>

void list_directory(const char *path, int show_hidden, int show_details) {
    DIR *dir = opendir(path);
    if (!dir) {
        fprintf(stderr, COLOR_RED "Error: Cannot open directory '%s'\n" COLOR_RESET, path);
        return;
    }

    printf(COLOR_BOLD COLOR_CYAN "\nDirectory: %s\n" COLOR_RESET, path);
    printf("%-40s %-10s %-12s %s\n", "Name", "Size", "Modified", "Permissions");
    printf("%-40s %-10s %-12s %s\n",
           "----------------------------------------",
           "----------", "------------", "-----------");

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL) {
        /* skip hidden files unless requested */
        if (!show_hidden && entry->d_name[0] == '.') continue;
        /* skip . and .. */
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        char full_path[MAX_PATH];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == -1) continue;

        int is_dir = S_ISDIR(st.st_mode);

        if (show_details) {
            char time_buf[20];
            struct tm *tm_info = localtime(&st.st_mtime);
            strftime(time_buf, sizeof(time_buf), "%Y-%m-%d", tm_info);

            if (is_dir) {
                printf(COLOR_BLUE "%-40s" COLOR_RESET, entry->d_name);
                printf(" %-10s %-12s ", "<DIR>", time_buf);
            } else {
                printf("%-40s ", entry->d_name);
                print_size(st.st_size);
                printf(" %-12s ", time_buf);
            }
            print_permissions(st.st_mode);
            printf("\n");
        } else {
            if (is_dir)
                printf(COLOR_BLUE "  [DIR] %s\n" COLOR_RESET, entry->d_name);
            else
                printf("  [FILE] %s\n", entry->d_name);
        }
        count++;
    }

    closedir(dir);
    printf(COLOR_YELLOW "\n  %d item(s) found.\n" COLOR_RESET, count);
}

int create_directory(const char *path) {
    if (mkdir(path, 0755) == 0) {
        printf(COLOR_GREEN "Created directory: %s\n" COLOR_RESET, path);
        return 1;
    }
    fprintf(stderr, COLOR_RED "Error: Could not create '%s'\n" COLOR_RESET, path);
    return 0;
}

int remove_directory(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        fprintf(stderr, COLOR_RED "Error: Cannot open '%s'\n" COLOR_RESET, path);
        return 0;
    }

    struct dirent *entry;
    char full_path[MAX_PATH];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == -1) continue;

        if (S_ISDIR(st.st_mode))
            remove_directory(full_path);
        else
            remove(full_path);
    }
    closedir(dir);

    if (rmdir(path) == 0) {
        printf(COLOR_GREEN "Removed directory: %s\n" COLOR_RESET, path);
        return 1;
    }
    fprintf(stderr, COLOR_RED "Error: Could not remove '%s'\n" COLOR_RESET, path);
    return 0;
}

void search_files(const char *dir, const char *pattern) {
    DIR *d = opendir(dir);
    if (!d) return;

    struct dirent *entry;
    char full_path[MAX_PATH];

    while ((entry = readdir(d)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == -1) continue;

        if (S_ISDIR(st.st_mode)) {
            search_files(full_path, pattern);
        } else {
            if (fnmatch(pattern, entry->d_name, FNM_CASEFOLD) == 0)
                printf(COLOR_GREEN "  Found: %s\n" COLOR_RESET, full_path);
        }
    }
    closedir(d);
}

long get_dir_size(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) return 0;

    long total = 0;
    struct dirent *entry;
    char full_path[MAX_PATH];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(full_path, &st) == -1) continue;

        if (S_ISDIR(st.st_mode))
            total += get_dir_size(full_path);
        else
            total += st.st_size;
    }
    closedir(dir);
    return total;
}

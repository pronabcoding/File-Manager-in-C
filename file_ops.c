#include "../include/file_manager.h"

#define BUFFER_SIZE 8192

int copy_file(const char *src, const char *dest) {
    FILE *in = fopen(src, "rb");
    if (!in) {
        fprintf(stderr, COLOR_RED "Error: Cannot open source '%s'\n" COLOR_RESET, src);
        return 0;
        
    }

    FILE *out = fopen(dest, "wb");
    if (!out) {
        fprintf(stderr, COLOR_RED "Error: Cannot create destination '%s'\n" COLOR_RESET, dest);
        fclose(in);
        return 0;
    }

    char buffer[BUFFER_SIZE];
    size_t bytes;
    long total = 0;

    while ((bytes = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        fwrite(buffer, 1, bytes, out);
        total += bytes;
    }

    fclose(in);
    fclose(out);

    printf(COLOR_GREEN "Copied: %s -> %s (" COLOR_RESET, src, dest);
    print_size(total);
    printf(COLOR_GREEN ")\n" COLOR_RESET);
    return 1;
}

int move_file(const char *src, const char *dest) {
    if (rename(src, dest) == 0) {
        printf(COLOR_GREEN "Moved: %s -> %s\n" COLOR_RESET, src, dest);
        return 1;
    }
    /* rename fails across filesystems, fall back to copy+delete */
    if (copy_file(src, dest)) {
        if (remove(src) == 0) {
            printf(COLOR_GREEN "Moved (cross-device): %s -> %s\n" COLOR_RESET, src, dest);
            return 1;
        }
    }
    fprintf(stderr, COLOR_RED "Error: Could not move '%s'\n" COLOR_RESET, src);
    return 0;
}

int delete_file(const char *path) {
    if (remove(path) == 0) {
        printf(COLOR_GREEN "Deleted: %s\n" COLOR_RESET, path);
        return 1;
    }
    fprintf(stderr, COLOR_RED "Error: Could not delete '%s'\n" COLOR_RESET, path);
    return 0;
}

int rename_file(const char *old_path, const char *new_path) {
    if (rename(old_path, new_path) == 0) {
        printf(COLOR_GREEN "Renamed: %s -> %s\n" COLOR_RESET, old_path, new_path);
        return 1;
    }
    fprintf(stderr, COLOR_RED "Error: Could not rename '%s'\n" COLOR_RESET, old_path);
    return 0;
}

void file_info(const char *path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        fprintf(stderr, COLOR_RED "Error: Cannot stat '%s'\n" COLOR_RESET, path);
        return;
    }

    char time_buf[64];
    struct tm *tm_info;

    printf(COLOR_BOLD "\n=== File Info: %s ===\n" COLOR_RESET, path);

    if (S_ISDIR(st.st_mode)) {
        printf("  Type        : " COLOR_BLUE "Directory\n" COLOR_RESET);
        long size = get_dir_size(path);
        printf("  Total Size  : ");
        print_size(size);
        printf("\n");
    } else {
        printf("  Type        : Regular File\n");
        printf("  Size        : ");
        print_size(st.st_size);
        printf("\n");
    }

    printf("  Permissions : ");
    print_permissions(st.st_mode);
    printf("\n");

    tm_info = localtime(&st.st_atime);
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("  Accessed    : %s\n", time_buf);

    tm_info = localtime(&st.st_mtime);
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("  Modified    : %s\n", time_buf);

    tm_info = localtime(&st.st_ctime);
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("  Changed     : %s\n", time_buf);

    printf("  Inode       : %lu\n", (unsigned long)st.st_ino);
    printf("  Hard Links  : %lu\n", (unsigned long)st.st_nlink);
}

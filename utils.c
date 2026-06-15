#include "../include/file_manager.h"

void print_size(long bytes) {
    if (bytes < 1024)
        printf("%ld B  ", bytes);
    else if (bytes < 1024 * 1024)
        printf("%.1f KB", bytes / 1024.0);
    else if (bytes < 1024 * 1024 * 1024)
        printf("%.1f MB", bytes / (1024.0 * 1024));
    else
        printf("%.1f GB", bytes / (1024.0 * 1024 * 1024));
}

void print_permissions(mode_t mode) {
    char perms[11];
    perms[0]  = S_ISDIR(mode)  ? 'd' : '-';
    perms[1]  = (mode & S_IRUSR) ? 'r' : '-';
    perms[2]  = (mode & S_IWUSR) ? 'w' : '-';
    perms[3]  = (mode & S_IXUSR) ? 'x' : '-';
    perms[4]  = (mode & S_IRGRP) ? 'r' : '-';
    perms[5]  = (mode & S_IWGRP) ? 'w' : '-';
    perms[6]  = (mode & S_IXGRP) ? 'x' : '-';
    perms[7]  = (mode & S_IROTH) ? 'r' : '-';
    perms[8]  = (mode & S_IWOTH) ? 'w' : '-';
    perms[9]  = (mode & S_IXOTH) ? 'x' : '-';
    perms[10] = '\0';
    printf("%s", perms);
}

void print_banner(void) {
    printf(COLOR_CYAN COLOR_BOLD);
    printf("╔══════════════════════════════════╗\n");
    printf("║       File Manager v%-12s║\n", VERSION);
    printf("║     Written in C  |  POSIX       ║\n");
    printf("╚══════════════════════════════════╝\n");
    printf(COLOR_RESET "\n");
}

void print_help(void) {
    printf(COLOR_BOLD "Usage:\n" COLOR_RESET);
    printf("  file_manager <command> [args...]\n\n");

    printf(COLOR_BOLD "Commands:\n" COLOR_RESET);
    printf("  " COLOR_YELLOW "ls" COLOR_RESET "   <path> [-a] [-l]   List directory contents\n");
    printf("                           -a: show hidden files\n");
    printf("                           -l: detailed listing\n\n");
    printf("  " COLOR_YELLOW "mkdir" COLOR_RESET " <path>             Create a directory\n");
    printf("  " COLOR_YELLOW "rmdir" COLOR_RESET " <path>             Remove a directory (recursive)\n");
    printf("  " COLOR_YELLOW "cp" COLOR_RESET "    <src> <dest>       Copy a file\n");
    printf("  " COLOR_YELLOW "mv" COLOR_RESET "    <src> <dest>       Move a file\n");
    printf("  " COLOR_YELLOW "rm" COLOR_RESET "    <path>             Delete a file\n");
    printf("  " COLOR_YELLOW "rn" COLOR_RESET "    <old> <new>        Rename a file\n");
    printf("  " COLOR_YELLOW "info" COLOR_RESET "  <path>             Show file/directory info\n");
    printf("  " COLOR_YELLOW "find" COLOR_RESET "  <dir> <pattern>    Search files (supports wildcards)\n");
    printf("  " COLOR_YELLOW "help" COLOR_RESET "                     Show this help\n\n");

    printf(COLOR_BOLD "Examples:\n" COLOR_RESET);
    printf("  ./file_manager ls . -l\n");
    printf("  ./file_manager cp notes.txt backup/notes.txt\n");
    printf("  ./file_manager find . \"*.c\"\n");
    printf("  ./file_manager info /home/user\n");
}

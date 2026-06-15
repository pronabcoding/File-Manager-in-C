#include "../include/file_manager.h"

int main(int argc, char *argv[]) {
    print_banner();

    if (argc < 2) {
        print_help();
        return 0;
    }

    const char *cmd = argv[1];

    /* ls <path> [-a] [-l] */
    if (strcmp(cmd, "ls") == 0) {
        const char *path = (argc >= 3) ? argv[2] : ".";
        int show_hidden  = 0;
        int show_details = 0;

        for (int i = 3; i < argc; i++) {
            if (strcmp(argv[i], "-a") == 0) show_hidden  = 1;
            if (strcmp(argv[i], "-l") == 0) show_details = 1;
        }
        list_directory(path, show_hidden, show_details);

    /* mkdir <path> */
    } else if (strcmp(cmd, "mkdir") == 0) {
        if (argc < 3) { fprintf(stderr, COLOR_RED "Usage: mkdir <path>\n" COLOR_RESET); return 1; }
        create_directory(argv[2]);

    /* rmdir <path> */
    } else if (strcmp(cmd, "rmdir") == 0) {
        if (argc < 3) { fprintf(stderr, COLOR_RED "Usage: rmdir <path>\n" COLOR_RESET); return 1; }
        printf(COLOR_YELLOW "Warning: This will recursively delete '%s'. Continue? [y/N]: " COLOR_RESET, argv[2]);
        char c = getchar();
        if (c == 'y' || c == 'Y')
            remove_directory(argv[2]);
        else
            printf("Aborted.\n");

    /* cp <src> <dest> */
    } else if (strcmp(cmd, "cp") == 0) {
        if (argc < 4) { fprintf(stderr, COLOR_RED "Usage: cp <src> <dest>\n" COLOR_RESET); return 1; }
        copy_file(argv[2], argv[3]);

    /* mv <src> <dest> */
    } else if (strcmp(cmd, "mv") == 0) {
        if (argc < 4) { fprintf(stderr, COLOR_RED "Usage: mv <src> <dest>\n" COLOR_RESET); return 1; }
        move_file(argv[2], argv[3]);

    /* rm <path> */
    } else if (strcmp(cmd, "rm") == 0) {
        if (argc < 3) { fprintf(stderr, COLOR_RED "Usage: rm <path>\n" COLOR_RESET); return 1; }
        printf(COLOR_YELLOW "Delete '%s'? [y/N]: " COLOR_RESET, argv[2]);
        char c = getchar();
        if (c == 'y' || c == 'Y')
            delete_file(argv[2]);
        else
            printf("Aborted.\n");

    /* rn <old> <new> */
    } else if (strcmp(cmd, "rn") == 0) {
        if (argc < 4) { fprintf(stderr, COLOR_RED "Usage: rn <old> <new>\n" COLOR_RESET); return 1; }
        rename_file(argv[2], argv[3]);

    /* info <path> */
    } else if (strcmp(cmd, "info") == 0) {
        if (argc < 3) { fprintf(stderr, COLOR_RED "Usage: info <path>\n" COLOR_RESET); return 1; }
        file_info(argv[2]);

    /* find <dir> <pattern> */
    } else if (strcmp(cmd, "find") == 0) {
        if (argc < 4) { fprintf(stderr, COLOR_RED "Usage: find <dir> <pattern>\n" COLOR_RESET); return 1; }
        printf(COLOR_CYAN "Searching for '%s' in '%s'...\n" COLOR_RESET, argv[3], argv[2]);
        search_files(argv[2], argv[3]);

    } else if (strcmp(cmd, "help") == 0 || strcmp(cmd, "--help") == 0) {
        print_help();

    } else {
        fprintf(stderr, COLOR_RED "Unknown command: '%s'\n" COLOR_RESET, cmd);
        print_help();
        return 1;
    }

    printf("\n");
    return 0;
}

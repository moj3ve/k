#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "repo.h"
#include "pkg.h"

char **REPOS = NULL;

void args(int argc, char *argv[]) {
    package *head = NULL;

    if (argc == 1) {
        printf("kiss [a|b|c|i|l|r|s|u|v] [pkg]...\n");
        printf("alternatives: List and swap to alternatives\n");
        printf("build:        Build a package\n");
        printf("checksum:     Generate checksums\n");
        printf("download:     Pre-download all sources\n");
        printf("install:      Install a package\n");
        printf("list:         List installed packages\n");
        printf("remove:       Remove a package\n");
        printf("search:       Search for a package\n");
        printf("update:       Check for updates\n");
        printf("version:      Package manager version\n");

        exit(0);
    }

    for (int i = 2; i < argc; i++) {
        pkg_load(&head, argv[i]);
    }

    while (head) {
        printf("%s\n", head->repository);
        head = head->next;
    }

    /* if (!strcmp(argv[1], "d") || !strcmp(argv[1], "download")) { */


    /* } else if (!strcmp(argv[1], "l") || !strcmp(argv[1], "list")) { */


    /* } else if (!strcmp(argv[1], "s") || !strcmp(argv[1], "search")) { */
    /*     for (int i = 2; i < argc; i++) { */
    /*         /1* path_find(argv[i], 1); *1/ */
    /*     } */

    /* } else if (!strcmp(argv[1], "v") || !strcmp(argv[1], "version")) { */
    /*     printf("3.0.3\n"); */
    /* } */
}

int main (int argc, char *argv[]) {
    REPOS = repo_load();
    args(argc, argv);
    return 0;
}

#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <libgen.h>
#include <stdint.h>
#include <sys/stat.h>

#include <sys/stat.h>
#include <ftw.h>

#include "find.h"
#include "log.h"
#include "util.h"
#include "pkg.h"

void pkg_load(package **head, char *pkg_name) {
    package *new_pkg = malloc(sizeof(package));    
    package *last = *head;

    if (!new_pkg)
        log_error("Failed to allocate memory");

    new_pkg->next        = NULL;
    new_pkg->name        = pkg_name;
    new_pkg->sums        = NULL;
    new_pkg->path        = NULL;
    new_pkg->source.src  = NULL;
    new_pkg->source.dest = NULL;
    new_pkg->src_len     = 0;
    new_pkg->path_len    = 0;

    pkg_find(new_pkg);

    if (!*head) {
        new_pkg->prev = NULL;
        *head = new_pkg;
        return;
    }

    while (last->next)
        last = last->next;

    last->next = new_pkg;
    new_pkg->prev = last;
}

void cache_init(void) {
    char cwd[PATH_MAX];
    char MAK_DIR[PATH_MAX + 1];
    char PKG_DIR[PATH_MAX + 1];
    char TAR_DIR[PATH_MAX + 1];
    pid_t pid = getpid();

    HOME = strdup(getenv("HOME"));

    if (!HOME || HOME[0] == '\0')
        log_error("HOME is NULL");

    SAVE_CWD
    CAC_DIR = strdup(getenv("XDG_CACHE_HOME"));

    if (!CAC_DIR || CAC_DIR[0] == '\0') {
        xchdir(HOME);
        mkdir(".cache", 0777);
        xchdir(".cache");
        
        free(CAC_DIR);
        CAC_DIR = strdup(getcwd(cwd, sizeof(cwd)));
    }

    mkdir(CAC_DIR, 0777);
    xchdir(CAC_DIR);

    mkdir("kiss", 0777);
    xchdir("kiss");

    free(CAC_DIR);
    CAC_DIR = strdup(getcwd(cwd, sizeof(cwd)));

    sprintf(MAK_DIR, "%s/build-%jd",   CAC_DIR, (intmax_t) pid);
    sprintf(PKG_DIR, "%s/pkg-%jd",     CAC_DIR, (intmax_t) pid);
    sprintf(TAR_DIR, "%s/extract-%jd", CAC_DIR, (intmax_t) pid);

    mkdir(MAK_DIR, 0777);
    xchdir(MAK_DIR);

    mkdir(PKG_DIR, 0777);
    xchdir(PKG_DIR);

    mkdir(TAR_DIR, 0777);
    xchdir(TAR_DIR);

    mkdir("../sources", 0777);
    xchdir("../sources");
    SRC_DIR = strdup(getcwd(cwd, sizeof(cwd)));

    mkdir("../bin", 0777);  
    xchdir("../bin");
    BIN_DIR = strdup(getcwd(cwd, sizeof(cwd)));

    LOAD_CWD;
}

static int rm(const char *fpath, const struct stat *sb, int tf, struct FTW *fb) {
    int rv;

    // Unused.
    (void)(sb);
    (void)(tf);
    (void)(fb);

    rv = remove(fpath);

    if (rv)
        log_warn("Failed to remove %s", fpath);

    return rv;
}

void cache_destroy(void) {
     nftw(MAK_DIR, rm, 64, FTW_DEPTH | FTW_PHYS);
     nftw(PKG_DIR, rm, 64, FTW_DEPTH | FTW_PHYS);
     nftw(TAR_DIR, rm, 64, FTW_DEPTH | FTW_PHYS);
}

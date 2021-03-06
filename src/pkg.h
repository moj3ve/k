#ifndef _KPKG_H
#define _KPKG_H

#define _POSIX_C_SOURCE 200809L
#include <limits.h> /* PATH_MAX */

extern char DB_DIR[PATH_MAX];

typedef struct package {
    char *name;
    char *ver;
    char *rel;

    /* location */
    char path[PATH_MAX];

    /* states */
    char mak_dir[PATH_MAX];
    char pkg_dir[PATH_MAX];
    char tar_dir[PATH_MAX];
    char  db_dir[PATH_MAX];

    /* caches */
    char src_dir[PATH_MAX];
    char bin_dir[PATH_MAX];

    char **sum;
    char **src;
    char **des;
    int  src_l;
    int  sum_l;

    char **dep;
    char **dep_type;
    int  dep_l;

    struct package *next;
    struct package *prev;
} package;

package *pkg_init(package **pkg, char *pkg_name);
void pkg_iter(package *pkg, void (*f)(package *pkg));
int pkg_have(char *pkg_name);
void pkg_state_init(package *pkg);
void pkg_destroy(package *pkg);
void pkg_destroy_all(void);

#endif

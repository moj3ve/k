#include <stdlib.h> /* size_t */
#include <stdio.h>  /* FILE */

void *xmalloc(size_t n);
int cntchr(const char *str, int chr);
void mkdir_p(const char *dir);
size_t int_to_str(int n, char *buf);
int cntlines(FILE *file);

#include <sys/stat.h>

char *strjoin(char *str, char *str2, char *delim);
int mkpath(char *path, mode_t mode, mode_t dir_mode);
void cache_init(void);

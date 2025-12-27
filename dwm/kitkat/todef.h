#ifndef TODEF_H
#define TODEF_H

#include <stdint.h>

typedef struct {
    char tag;
    char value[256];
} TagEntry;

void run_command(const char *cmd, char *output, size_t size);
int read_file(const char *path, char *buf, size_t size);

#endif

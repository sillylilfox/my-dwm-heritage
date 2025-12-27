#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "argparser.h"

void build_status(const char *format, TagEntry *tags, int n_tags, char *status, size_t size) {
    status[0] = '\0';
    for (const char *p = format; *p; p++) {
        if (*p == '%' && *(p + 1)) {
            p++;
            int found = 0;
            for (int i = 0; i < n_tags; i++) {
                if (tags[i].tag == *p) {
                    strncat(status, tags[i].value, size - strlen(status) - 1);
                    found = 1;
                    break;
                }
            }
            if (!found)
                strncat(status, (char[]){'%', *p, 0}, size - strlen(status) - 1);
        } else {
            strncat(status, (char[]){*p, 0}, size - strlen(status) - 1);
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "todef.h"
#include <string.h>
#include <fcntl.h>

int read_file(const char *path, char *buf, size_t size) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return -1;
    ssize_t n = read(fd, buf, size - 1);
    close(fd);
    if (n <= 0) return -1;
    buf[n] = '\0';
    char *nl = strchr(buf, '\n');
    if (nl) *nl = '\0';
    return 0;
}

void run_command(const char *cmd, char *output, size_t size) {
    FILE *fp = popen(cmd, "r");
    if (!fp) {
        snprintf(output, size, "Error");
        return;
    }
    if (fgets(output, size, fp) != NULL) {
        output[strcspn(output, "\n")] = 0;
    } else {
        snprintf(output, size, "N/A");
    }
    pclose(fp);
}


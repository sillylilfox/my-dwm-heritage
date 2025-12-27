#include <stdio.h>
#include <stdlib.h>
#include "mautil.h"
#include "argparser.h"
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "todef.h"

static void st_ch(void* status) {
    printf("%s\n",(char*)status);
    fflush(stdout);
}

static void (*jump_table[])(void*) = {
    st_ch,
    write_into_xroot
};

static void display_help(const char* a) { 
    printf("Usage: %s <output> <refresh time> <format string>\n", a);
    printf("Output options: stdout, xsetroot, logfile\n");
    printf("Placeholders: %%b %%c %%r %%h %%m %%o %%d %%i %%s\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        display_help(argv[0]);
        return 1;
    }

    char status[512];
    //char format[256] = "%b|%c|%r|%h:%m";
    const char *format = argv[3];
    int refreshtime = atoi(argv[2]);
    const char *out = argv[1];
    int jt;

    if(strcmp(out, "stdout") == 0) jt = 0;
    else if(strcmp(out, "xsetroot") == 0) jt = 1;
    else {display_help(argv[0]); return 1;}

    TagEntry tags[9];
    
    while (1) {
        update_tags(tags);
        build_status(format, tags, 9, status, sizeof(status));
        
        /*Do whatever you want to do here. The code's heart is here*/
        jump_table[jt](status);

        sleep(refreshtime);
    }

    return 0;
}

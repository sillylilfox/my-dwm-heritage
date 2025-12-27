#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "mautil.h"
#include "todef.h"

void update_battery(TagEntry *tag) {
    const char *paths[] = {
        "/sys/class/power_supply/BAT0/capacity",
        "/sys/class/power_supply/BAT1/capacity",
    };

    for (size_t i = 0; i < sizeof(paths)/sizeof(paths[0]); i++) {
        if (read_file(paths[i], tag->value, sizeof(tag->value)) == 0) {
            tag->tag = 'b';
            return;
        }
    }

    strncpy(tag->value, "N/A", sizeof(tag->value));
    tag->value[sizeof(tag->value) - 1] = '\0';
    tag->tag = 'b';
}

void update_cpu(TagEntry *tag) {
    run_command("top -bn1 | grep \"Cpu(s)\" | sed \"s/.*, *\\([0-9.]*\\)%* id.*/\\1/\" | awk '{print 100 - $1\"%\"}'",
                tag->value, sizeof(tag->value));
    tag->tag = 'c';
}

void update_ram(TagEntry *tag) {
    run_command("free -h | awk '/^Mem/ {print $3 \"/\" $2}'", tag->value, sizeof(tag->value));
    tag->tag = 'r';
}

void update_hour(TagEntry *tag) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(tag->value, sizeof(tag->value), "%02d", tm.tm_hour);
    tag->tag = 'h';
}

void update_minute(TagEntry *tag) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(tag->value, sizeof(tag->value), "%02d", tm.tm_min);
    tag->tag = 'm';
}

void update_day(TagEntry *tag) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(tag->value, sizeof(tag->value), "%02d", tm.tm_mday);
    tag->tag = 'd';
}

void update_month(TagEntry *tag) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(tag->value, sizeof(tag->value), "%02d", tm.tm_mon + 1);
    tag->tag = 'o';
}

void update_mic(TagEntry *tag) {
    run_command("amixer get Capture | awk -F'[][]' 'END{print $2}'", tag->value, sizeof(tag->value));
    tag->tag = 'i';
}

void update_speaker(TagEntry *tag) {
    run_command("amixer get Master | awk -F'[][]' 'END{print $2}'", tag->value, sizeof(tag->value));
    tag->tag = 's';
}

void update_tags(TagEntry *tags) {
    update_battery(&tags[0]);
    update_cpu(&tags[1]);
    update_ram(&tags[2]);
    update_hour(&tags[3]);
    update_minute(&tags[4]);
    update_day(&tags[5]);
    update_month(&tags[6]);
    //update_mic(&tags[7]);
    //update_speaker(&tags[8]);
}

void write_into_xroot(void* status) {
    char cmd[768]; //it should be set to x times 3
    snprintf(cmd, sizeof(cmd), "xsetroot -name \"%s\"", (char*)status);
    system(cmd);
}


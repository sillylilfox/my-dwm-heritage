#ifndef MAUTIL_H
#define MAUTIL_H

#include "todef.h"

void update_battery(TagEntry *tag);
void update_cpu(TagEntry *tag);
void update_ram(TagEntry *tag);
void update_hour(TagEntry *tag);
void update_minute(TagEntry *tag);
void update_day(TagEntry *tag);
void update_month(TagEntry *tag);
void update_mic(TagEntry *tag);
void update_speaker(TagEntry *tag);
void update_tags(TagEntry *tags);

void write_into_xroot(void* status);

#endif

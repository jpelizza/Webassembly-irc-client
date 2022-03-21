#include <emscripten/emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ems_irc.h"

extern irc_t *irc;

struct p_info {
    unsigned short flag;
    char command[1024];
    char channel[1024];
    char who_nick[1024];
    char who_user[1024];
    char who_server[1024];
    char msg[1024];
};

int p_info_init(struct p_info *pi);
int parse_irc(const char *msg);
void str_until_char(char *dest, const char *source, char from, char until);
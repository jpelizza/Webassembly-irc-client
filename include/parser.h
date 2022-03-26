#ifndef EMS_IRC
#define EMS_IRC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ems_irc.h"

extern irc_t irc;

struct p_info {
    unsigned short flag;
    char command[16];
    char channel[32];
    char who_nick[32];
    char who_user[64];
    char sever[64];
    char msg[1024];
};

enum COMMAND_FLAGS { PRIVMSG, PING, USER_LIST, LOGIN, JOIN_CHAN };

struct p_info parse_irc(char *msg);

#endif
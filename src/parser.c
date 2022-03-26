#include "../include/parser.h"

struct p_info parse_irc(char *msg) {
    struct p_info parsed_msg = {-1, "-", "-", "-", "-", "-", "-"};

    if (strstr(msg, "PRIVMSG") != NULL) {
        parsed_msg.flag = PRIVMSG;
        strcpy(parsed_msg.who_nick, strtok(msg + 1, "!"));
        strcpy(parsed_msg.who_user, strtok(NULL, "@"));
        strcpy(parsed_msg.sever, strtok(NULL, " "));
        strcpy(parsed_msg.command, strtok(NULL, " "));
        strcpy(parsed_msg.channel, strtok(NULL, " "));
        strcpy(parsed_msg.msg, strtok(NULL, ":"));
    } else if (strstr(msg, "PING") != NULL) {
        parsed_msg.flag = PING;
        strcpy(parsed_msg.command, strtok(msg, " "));
        strcpy(parsed_msg.msg, strtok(NULL, ":"));
    } else if (strstr(msg, "Message of the day file is missing.") != NULL) {
        parsed_msg.flag = JOIN_CHAN;
    } else {
        printf("Non parsed message:\n%s\n", msg);
    }

    return parsed_msg;
}
#include "../include/parser.h"

short int connected = 0;

int p_info_init(struct p_info *pi) {
    if (pi == NULL)
        pi = (struct p_info *)malloc(sizeof(struct p_info));
    pi->flag = 0;
    return 0;
}

int p_info_free(struct p_info *pi) {
    free(pi);
    return 0;
}

void parse_login(const char *msg) {
    if (strstr(msg, "Could not resolve your hostname") != NULL) {
        emscripten_run_script("login()");
    } else if (strstr(msg, "Message of the day file is missing.") != NULL) {
        irc_join_channel(irc);
        connected = 1;
    }
}

struct p_info *fill(const char *msg) {
    struct p_info *parsed_msg;
    p_info_init(parsed_msg);

    char *token = (char *)malloc(sizeof(char) * strlen(msg));
    char *copy_msg = (char *)malloc(sizeof(char) * strlen(msg));
    strcpy(copy_msg, msg);
    token = strtok(copy_msg, " ");
    if (!strcmp(token, "PING")) {
        irc_pong(irc, msg);
        return NULL;
    }

    strcpy(copy_msg, msg);
    if (strstr(token, "PRIVMSG") != NULL) {
        strcpy(parsed_msg->who_nick, strtok(copy_msg + 1, "!"));
        strcpy(parsed_msg->who_user, strtok(NULL, "@"));
        strcpy(parsed_msg->who_server, strtok(NULL, " "));
        strcpy(parsed_msg->command, strtok(NULL, " "));
        strcpy(parsed_msg->channel, strtok(NULL, " "));
        strcpy(parsed_msg->msg, strtok(NULL, ":"));
    }

    return parsed_msg;
}

int parse_irc(const char *msg) {
    if (!connected)
        parse_login(msg);

    struct p_info *parsed_msg = fill(msg);

    if (!strcmp(parsed_msg->command, "PRIVMSG")) {
        char recv_msg[256] = {'\0'};
        strcat(recv_msg, "recv_msg(\"");
        strcat(recv_msg, parsed_msg->msg);
        strcat(recv_msg, "\")");
        printf("%s\n", recv_msg);
        emscripten_run_script(recv_msg);
    }
    printf("%s\n", parsed_msg->msg);

    p_info_free(parsed_msg);
    return 0;
}

/**
 * @brief Copies from 'souce' to 'dest' from char 'from' until 'until' neither of which is included
 *
 * @param dest
 * @param source
 * @param from
 * @param until
 * @return void
 */
void str_until_char(char *dest, const char *source, char from, char until) {
    int aux = (char *)strchr(source, until) - (char *)strchr(source, from);
    if (from != '\0')
        strncpy(dest, strchr(source, from) + 1, aux - 1);
    if (from == until) {
        aux = (char *)strchr(source + 1, until) - (char *)strchr(source, from);
        strncpy(dest, strchr(source, from) + 1, aux - 1);
    } else
        strncpy(dest, source, strchr(source, until) - source);
}
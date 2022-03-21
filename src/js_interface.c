#include "../include/js_interface.h"

irc_t *irc = NULL;

void wsirc_socket_config(int w_socket) {
    // if already configured then ignores
    if (irc != NULL)
        return;
    // else configures
    irc = (irc_t *)malloc(sizeof(irc_t));
    irc->s = w_socket;
    return;
}

EMSCRIPTEN_KEEPALIVE void wsirc_config(const char *chan, const char *nick) {
    irc->channel = (char *)malloc(sizeof(char) * strlen(chan) + 1);
    irc->nick = (char *)malloc(sizeof(char) * strlen(nick) + 1);
    strcpy(irc->nick, nick);
    strcpy(irc->channel, chan);
    return;
}

EMSCRIPTEN_KEEPALIVE int wsirc_login() {
    if (irc != NULL && irc->nick != NULL && irc->channel != NULL) {
        printf("login %d\n", irc_login(irc));
        return 0;
    }
    return 1;
}

EMSCRIPTEN_KEEPALIVE int wsirc_send_msg(const char *msg) { return irc_send_msg(irc, msg); }

// EMSCRIPTEN_KEEPALIVE const char *wsirc_get_users() { return ""; }

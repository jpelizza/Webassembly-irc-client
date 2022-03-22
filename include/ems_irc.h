#ifndef IRC_H
#define IRC_H

#include <emscripten/websocket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    // structure info
    int s;
    // user info
    char *channel;
    char *nick;
} irc_t;

int ems_send(int s, const char *msg);

int irc_join_channel(irc_t *irc);
int irc_login(irc_t *irc);
int irc_pong(irc_t *irc, const char *msg);
int irc_send_msg(irc_t *irc, const char *msg);
int irc_reply_message(irc_t *irc, char *msg);
int irc_get_user_list(irc_t *irc);

// IRC Proto
int _irc_join(int s, const char *channel);
int _irc_msg(int s, const char *channel, const char *data);
int _irc_nick(int s, const char *nick);
int _irc_part(int s, const char *data);
int _irc_pong(int s, const char *pong);
int _irc_quit(int s, const char *quit_msg);
int _irc_reg(int s, const char *nick, const char *user, const char *hostname, const char *fullname);
int _irc_topic(int s, const char *channel, const char *data);
int _irc_names(int s, char *channel);

#endif

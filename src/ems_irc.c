#include "../include/ems_irc.h"

/**
 * @brief Emscripten websocket alternative to barkleys' socket send
 *
 * @param s socket
 * @param msg message string sent as utf8_text
 * @return int error code, if 0 then success
 */
int ems_send(int s, const char *msg) { return emscripten_websocket_send_utf8_text(s, msg); };

/**
 * @brief Login into server given irc settings
 *
 * @param irc irc_t
 * @return int return emscripten_websocket_send_utf8_text flag
 */
int irc_login(irc_t *irc) { return _irc_reg(irc->s, irc->nick, "u", "h", "f"); }

/**
 * @brief Join channel given irc settings
 *
 * @param irc irc_t
 * @return int return emscripten_websocket_send_utf8_text flag
 */
int irc_join_channel(irc_t *irc) { return _irc_join(irc->s, irc->channel); }

/**
 * @brief Asks channel's user list given irc settings
 *
 * @param irc irc_t
 * @return int return emscripten_websocket_send_utf8_text flag
 */
int irc_get_user_list(irc_t *irc) { return _irc_names(irc->s, irc->channel); }

/**
 * @brief send privmsg to channel given irc settings
 *
 * @param irc  irc_t
 * @param msg  message to be sent
 * @return int return emscripten_websocket_send_utf8_text flag
 */
int irc_send_msg(irc_t *irc, const char *msg) {
    _irc_msg(irc->s, irc->channel, msg);
    return 0;
}

/**
 * @brief Responds to ping
 *
 * @param irc irc_t settings
 * @param server server to return ping to
 * @return int
 */
int irc_pong(irc_t *irc, const char *server) {
    char *serv = (char *)malloc(sizeof(server));
    strcpy(serv, server + 6);
    return _irc_pong(irc->s, serv);
}

/**
 * @brief IRC COMMOM PROTOCOL FUNC
 * This will not be commented, be sure to make a test.c to confirm all these functions work correctly
 * base on https://github.com/Themaister/simple-irc-bot, and by "based on" I mean I took it out of lazyness to make my
 * own.
 */

// irc_pong: For answering pong requests...
int _irc_pong(int s, const char *data) {
    char *buf;
    size_t sz = snprintf(NULL, 0, "PONG :%s\r\n", data);
    buf = (char *)malloc(sz + 1);
    snprintf(buf, sz + 1, "PONG :%s\r\n", data);
    return ems_send(s, buf);
}

// irc_reg: For registering upon login
int _irc_reg(int s, const char *nick, const char *user, const char *hostname, const char *fullname) {
    char *buf[2];
    size_t sz[2];
    sz[0] = snprintf(NULL, 0, "NICK %s\r\n", nick);
    buf[0] = (char *)malloc(sz[0] + 1);
    snprintf(buf[0], sz[0] + 1, "NICK %s\r\n", nick);

    sz[1] = snprintf(NULL, 0, "USER %s localhost 0 :%s\r\n", "username", "fullname");
    buf[1] = (char *)malloc(sz[1] + 1);
    snprintf(buf[1], sz[1] + 1, "USER %s localhost 0 :%s\r\n", "username", "fullname");

    EMSCRIPTEN_RESULT result;
    for (int i = 0; i < 2; i++) {
        result = ems_send(s, buf[i]);
        if (result != 0) {
            printf("%d - Error code %d :  _irc_reg", i, result);
        }
    }

    return result;
}

// irc_join: For joining a channel
int _irc_join(int s, const char *data) {
    char *buf;
    size_t sz = snprintf(NULL, 0, "JOIN %s\r\n", data);
    buf = (char *)malloc(sz + 1);
    snprintf(buf, sz + 1, "JOIN %s\r\n", data);
    return ems_send(s, buf);
}

// irc_part: For leaving a channel
int _irc_part(int s, const char *data) {
    char *buf;
    size_t sz = snprintf(NULL, 0, "PART %s\r\n", data);
    buf = (char *)malloc(sz + 1);
    snprintf(buf, sz + 1, "PART %s\r\n", data);
    return ems_send(s, buf);
}

// irc_nick: For changing your nick
int _irc_nick(int s, const char *data) {
    char *buf;
    size_t sz = snprintf(NULL, 0, "NICK %s\r\n", data);
    buf = (char *)malloc(sz + 1);
    snprintf(buf, sz + 1, "NICK %s\r\n", data);
    return ems_send(s, buf);
}

// irc_quit: For quitting IRC
int _irc_quit(int s, const char *data) {
    char *buf;
    size_t sz = snprintf(NULL, 0, "QUIT :%s\r\n", data);
    buf = (char *)malloc(sz + 1);
    snprintf(buf, sz + 1, "QUIT :%s\r\n", data);
    return ems_send(s, buf);
}

// irc_topic: For setting or removing a topic
int _irc_topic(int s, const char *channel, const char *data) {
    char *buf;
    size_t sz = snprintf(NULL, 0, "TOPIC %s :%s\r\n", channel, data);
    buf = (char *)malloc(sz + 1);
    snprintf(buf, sz + 1, "TOPIC %s :%s\r\n", channel, data);
    return ems_send(s, buf);
}

// irc_msg: For sending a channel message or a query
int _irc_msg(int s, const char *channel, const char *data) {
    char *buf;
    size_t sz = snprintf(NULL, 0, "PRIVMSG %s :%s\r\n", channel, data);
    buf = (char *)malloc(sz + 1);
    snprintf(buf, sz + 1, "PRIVMSG %s :%s\r\n", channel, data);
    return ems_send(s, buf);
}

// irc_msg: For asking server list of usernames
int _irc_names(int s, char *channel) {
    char *buf;
    size_t sz = snprintf(NULL, 0, "NAMES %s\r\n", channel);
    buf = (char *)malloc(sz + 1);
    snprintf(buf, sz + 1, "NAMES %s\r\n", channel);
    return ems_send(s, buf);
}

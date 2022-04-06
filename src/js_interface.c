#include "../include/js_interface.h"

irc_t irc = {-1};

/**
 * @brief Function should be called as soon as connection opens,
 * saves socket tha will be used forward
 *
 * @param w_socket
 */
void wsirc_socket_config(int w_socket) {
  // if already configured then ignores
  irc.s = w_socket;
  return;
}

/**
 * @brief Requests list of users on channel ','
 */
void wsirc_get_userlist() { irc_get_user_list(&irc); }

/**
 * @brief This function is exported.
 * Configures global struct irc_p 'irc' with channel and nickname.
 *
 * @param chan channel to connect to
 * @param nick nicknme to connect with
 * @return void
 */
EMSCRIPTEN_KEEPALIVE void wsirc_config(const char *chan, const char *nick) {
  irc.channel = (char *)malloc(sizeof(char) * strlen(chan) + 1);
  irc.nick = (char *)malloc(sizeof(char) * strlen(nick) + 1);
  strcpy(irc.nick, nick);
  strcpy(irc.channel, chan);
  return;
}

/**
 * @brief This function is exported.
 * Logs in to irc based on previos configurations of functions:
 * wsirc_socket_config and wsirc_config
 *
 * @return void
 */
EMSCRIPTEN_KEEPALIVE int wsirc_login() {
  if (irc.nick != NULL && irc.channel != NULL) {
    printf("login %d\n", irc_login(&irc));
    return 0;
  }
  return 1;
}

/**
 * @brief This function is exported
 *
 * @param msg text string to be sent as utf_8
 * @return int result of emscripten_websocket_send_utf8_text, if 0 then
 * successful
 */
EMSCRIPTEN_KEEPALIVE int wsirc_send_msg(const char *msg) {
  return irc_send_msg(&irc, msg);
}

/**
 * @brief return websocket connection integer used on irc connection
 *
 * @return EMSCRIPTEN_KEEPALIVE
 */
EMSCRIPTEN_KEEPALIVE int wsirc_get_ws() { return irc.s; }

// EMSCRIPTEN_KEEPALIVE const char *wsirc_get_users() { return ""; }

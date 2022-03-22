#ifndef JS_INTERFACE
#define JS_INTERFACE

#include "ems_irc.h"
#include <emscripten/websocket.h>

void wsirc_socket_config(int w_socket);
void wsirc_config(const char *chan, const char *nick);

#endif
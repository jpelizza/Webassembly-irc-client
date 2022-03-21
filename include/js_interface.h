#ifndef js_interface
#define js_interface

#include "ems_irc.h"
#include <emscripten/emscripten.h>
#include <emscripten/websocket.h>

void wsirc_socket_config(int w_socket);
void wsirc_config(const char *chan, const char *nick);

#endif
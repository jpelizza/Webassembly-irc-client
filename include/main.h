#include <emscripten/emscripten.h>
#include <emscripten/websocket.h>
#include <stdio.h>
#include <stdlib.h>

#include "ems_irc.h"
#include "js_interface.h"
#include "parser.h"

extern irc_t *irc;

EM_BOOL onmessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData);
EM_BOOL onclose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent, void *userData);
EM_BOOL onopen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent, void *userData);
EM_BOOL onerror(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent, void *userData);

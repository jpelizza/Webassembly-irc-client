#include <emscripten/emscripten.h>
#include <emscripten/websocket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ems_irc.h"
#include "js_interface.h"
#include "parser.h"

extern irc_t *irc;

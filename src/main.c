// $ em++ -lwebsocket.js -o index.html main.cpp
#include "../include/main.h"

/**
 * @brief onOpen is used as a callback to websocket created on main
 * it's called by a signal as soon as the websocket is confirmed to be opened
 *
 * @param eventType
 * @param websocketEvent
 * @param userData
 * @return EM_BOOL
 */
EM_BOOL onopen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent, void *userData) {
    wsirc_socket_config(websocketEvent->socket);
    return EM_TRUE;
}
EM_BOOL onerror(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent, void *userData) { return EM_TRUE; }
EM_BOOL onclose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent, void *userData) { return EM_TRUE; }
/**
 * @briefonMessage is used as a callback when the websocket receives a message
 * userdata is information received, this information will be parsed and returned as a p_info structure
 * from there on it'll use a switch case scenario to respond correctly to each message
 *
 * @param eventType
 * @param websocketEvent
 * @param userData
 * @return EM_BOOL
 */
EM_BOOL onmessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData) {
    char ems_script[2048];
    struct p_info parsed = parse_irc((char *)websocketEvent->data);

    switch (parsed.flag) {
    case PRIVMSG:
        printf("PRIVMSG\n");
        sprintf(ems_script, "recv_msg('%s')", parsed.msg);
        emscripten_run_script(ems_script);
        break;

    case PING:
        printf("PING\n");
        irc_pong(irc, parsed.msg);
        break;

    case LOGIN:
        emscripten_run_script("login()");
        break;

    case JOIN_CHAN:
        irc_join_channel(irc);
        break;

    default:

        break;
    }

    return EM_TRUE;
}

int main(int argc, char *argv[]) {
    if (!emscripten_websocket_is_supported()) {
        return 0;
    }

    // ws setup: url, flags, create_on_main_thread
    EmscriptenWebSocketCreateAttributes ws_attrs = {"ws://127.0.0.1:7002", NULL, EM_TRUE};
    // creates websocket
    EMSCRIPTEN_WEBSOCKET_T ws = emscripten_websocket_new(&ws_attrs);

    // callbacks setup on signals
    emscripten_websocket_set_onopen_callback(ws, NULL, onopen);
    emscripten_websocket_set_onerror_callback(ws, NULL, onerror);
    emscripten_websocket_set_onmessage_callback(ws, NULL, onmessage);
    emscripten_websocket_set_onclose_callback(ws, NULL, onclose);
}
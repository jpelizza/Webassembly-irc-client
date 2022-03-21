// $ em++ -lwebsocket.js -o index.html main.cpp
#include "../include/main.h"

EM_BOOL onopen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent, void *userData) {
    printf("onopen\n");
    wsirc_socket_config(websocketEvent->socket);

    return EM_TRUE;
}
EM_BOOL onerror(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent, void *userData) {
    // printf("onerror\n");
    return EM_TRUE;
}
EM_BOOL onclose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent, void *userData) {
    // printf("onclose\n");
    return EM_TRUE;
}
EM_BOOL onmessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData) {
    // printf("onmessage\n");
    if (websocketEvent->isText) {
        // For only ascii chars.
        printf("%s\n", websocketEvent->data);
    }
    parse_irc((char *)websocketEvent->data);

    return EM_TRUE;
}

int main(int argc, char *argv[]) {
    if (!emscripten_websocket_is_supported()) {
        return 0;
    }

    EmscriptenWebSocketCreateAttributes ws_attrs = {"ws://127.0.0.1:7002", NULL, EM_TRUE};

    EMSCRIPTEN_WEBSOCKET_T ws = emscripten_websocket_new(&ws_attrs);

    emscripten_websocket_set_onopen_callback(ws, NULL, onopen);
    emscripten_websocket_set_onerror_callback(ws, NULL, onerror);
    emscripten_websocket_set_onmessage_callback(ws, NULL, onmessage);
    emscripten_websocket_set_onclose_callback(ws, NULL, onclose);
}
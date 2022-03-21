all:
	emcc -lwebsocket.js -s MODULARIZE -s EXPORTED_RUNTIME_METHODS=ccall -s PROXY_POSIX_SOCKETS=1 \
	./src/main.c ./src/ems_irc.c ./src/js_interface.c ./src/parser.c -o wasm_irc.js

clean:
	rm *.wasm *.js *.html
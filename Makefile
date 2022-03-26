CC := emcc
CFLAGS := -lwebsocket.js -s MODULARIZE -s EXPORTED_RUNTIME_METHODS=ccall -s PROXY_POSIX_SOCKETS=1
BIN_DIR := ./bin
SRC_DIR := ./src
BUILD_DIR := ./build

OBJECTS  := $(BIN_DIR)/*.o
SOURCES  := $(SRC_DIR)/*.c

TARGET := wasm_irc.js

wasm_irc : folders main.o ems_irc.o js_interface.o parser.o
	$(CC) $(OBJECTS)	$(CFLAGS) -o $(BUILD_DIR)/$(TARGET)

folders:
	[-d $(BIN_DIR) ] || mkdir -p $(BIN_DIR)
	[-d $(BUILD_DIR) ] || mkdir -p $(BUILD_DIR)

main.o: 
	emcc -c $(SRC_DIR)/main.c -o $(BIN_DIR)/main.o 

parser.o: 
	emcc -c $(SRC_DIR)/parser.c -o $(BIN_DIR)/parser.o

js_interface.o: 
	emcc -c $(SRC_DIR)/js_interface.c -o $(BIN_DIR)/js_interface.o

ems_irc.o: 
	emcc -c $(SRC_DIR)/ems_irc.c -o $(BIN_DIR)/ems_irc.o

clean:
	rm $(BUILD_DIR)/*.wasm $(BUILD_DIR)/*.js $(BIN_DIR)/*.o
## Gag

Throughout humankind, from caveman, to philosophers, to scientists, the question of: How could one have enough computer resources to run two 4K videos streams and the latest AAA video-game on max settings while also having a web irc client running on the side? That's preposterous!

Not anymore! Introducing: a simple WebAssembly IRC client, finally you can manage your resources without dropping any frames!



## Project

#### What is it? 
This is an in-progress web socket IRC client written in C and compiled to WebAssembly, it's supposed to be single channel.
Objectives as of now are configuring desired channel and nickname and having functionalities as far as receiving and sending messages.

#### How I ended up making this:
I really like streaming websites, I really dislike depending on other's services to stream.
While programming my own forum with streaming capabilities using [CPPCMS](https://github.com/artyom-beilis) I encountered an issue, I couldn't find a simple web client, most of them use bouncers and gateways and honestly it seemed a bit overwhelming to use for something as simple as a one channel, send and receive message client on my website.

I turned this issue on a opportunity to learn WebAssembly using [Emscripten](https://github.com/emscripten-core/emscripten).

#### What I hope to accomplish:
An IRC web client not unlike one seen on twitch, youtube and dlive.


## How to get it running

#### IRC Server

For this project I was using [inspIRCd](https://github.com/inspircd/inspircd) with the following config file.

```c++
#-#-#-#-#-#-#-#-#-#-#-#-     WEB SOCK CONF     -#-#-#-#-#-#-#-#-#-#-#-
<module name="sha1">
<module name="websocket">
<websocket defaultmode="text">
<wsorigin allow="*">
<bind address="127.0.0.1" port="7002" hook="websocket">
```

#### Compiling
As of now the server is static, before compiling change the IP address to connect to on main.c's main main function
```c
EmscriptenWebSocketCreateAttributes ws_attrs = {"ws://127.0.0.1:7002", NULL, EM_TRUE};
```
Compile with `make`

#### Testing
Run test.html on your browser and open console, as soon as you join a channel you can use the send button and text input to send messages to the IRC chat

#### Debug
If by any chance you get a CORS error then you'll have to explicitly enable CORS sharing, you can do that easly with [this python script](https://gist.github.com/khalidx/6d6ebcd66b6775dae41477cffaa601e5), now all you have to do is change on your test.html 
```js
<script src="./wasm_irc.js">/*IMPORT*/</script>
```
to access your python server such as:
```js
<script src="http:localhost:8000/wasm_irc.js">/*IMPORT*/</script>
```
---
## TODO
##### In no particular order the next steps ares:

+ Use arguments to connect to the server on webassembly, using argc and argv is simples but I'm not yet sure on how to set arguments on JS's Module call yet. 
+ ~~Comment code.~~
+ Build a better Makefile, right now it's a glorified static shell call.
+ Refactor parser
  - ~~such as no more need for `parse_login`~~. 
  - ~~maybe set `fill`'s content to parse_irc~~
  - ~~take out `emscripten_run_script` out of parser, as it's supposed to only parse message into struct `p_info`, let all messages handling be made by `onmessage` or create another handler that responds if needed~~
+ Make a better user interface on html+js end.
+ Create simple test runs to facilitate future development

##### In no particular order what I wish to support in the future:
+ Userlist
+ Add direct messaging support, e.g: `/pm @foo bar` and message "bar" only showing on foo's chat. 

---

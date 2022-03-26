// STARTUP AND CONFIG
channel = "#chan";
nickname = Math.random().toString(36).replace(/[^a-z]+/g, '').substring(0, 5);
let irc_ws = -1;
const m = init();
config_conn(channel, nickname);

async function init() {
  const module = await Module();
  return module;
}

function config_conn(chan, nick) {
  m.then((result) => {
    result.ccall('wsirc_config', null, ["string", "string"], [chan, nick]);
    login();
  })
}

function login() {
  m.then((result) => {
    let i_id = setInterval(() => {
      if (result.ccall('wsirc_get_ws', ['number'], [], []) == -1) {
        return;
      }
      result.ccall('wsirc_login', ["number"], [], []);
      document.getElementById("send").disabled = false;
      clearInterval(i_id);
    }, 1000);
  })
}

// FUNCTIONS TO BE CALLED WHILE RUNNING
function send_msg(msg) {
  m.then((result) => {
    msg = document.getElementById('content').value;
    if (msg == "") return;
    result.ccall('wsirc_send_msg', null, ["string"], [msg]);
    recv_msg(nickname + " :" + msg);
    document.getElementById('content').value = "";
  })
}

function recv_msg(msg) {
  var ul = document.getElementById("messages");
  var li = document.createElement("li");
  li.appendChild(document.createTextNode(msg));
  ul.appendChild(li);
}


function get_user_list() {
  m.then((result) => {
    result.ccall('wsirc_send_msg', ["string"], [], []);
  })
}

document.addEventListener("keydown",
  function (event) {
    if (event.key == "Enter" && !document.getElementById("send").disabled) {
      send_msg();
    }
  }, false);
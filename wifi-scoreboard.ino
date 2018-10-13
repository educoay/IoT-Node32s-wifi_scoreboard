#include <ShiftRegister74HC595.h>
#include <WiFiClient.h>
#include <ESP32WebServer.h>
#include <WiFi.h>

const char* ssid = "wifi-ssid";
const char* password = "wifi-password";

ESP32WebServer server(80);

// create a global shift register object
// parameters: (number of shift registers, data pin, clock pin, latch pin)
int dataPin1 = 32;
int clockPin1 = 33;
int latchPin1 = 25;
ShiftRegister74HC595 homeScr (3, dataPin1, clockPin1, latchPin1);

int dataPin2 = 26;
int latchPin2 = 27;
int clockPin2 = 14;
ShiftRegister74HC595 awayScr (3, dataPin2, clockPin2, latchPin2);

int oneDef[] = {1, 2};
int twoDef[] = {0, 1, 3, 4, 6};
int threeDef[] = {0, 1, 2, 3, 6};
int fourDef[] = {1, 2, 5, 6};
int fiveDef[] = {0, 2, 3, 5, 6};
int sixDef[] = {0, 2, 3, 4, 5, 6};
int sevenDef[] = {0, 1, 2};
int eightDef[] = {0, 1, 2, 3, 4, 5, 6};
int nineDef[] = {0, 1, 2, 5, 6};
int zeroDef[] = {0, 1, 2, 3, 4, 5};

//add persistent value when refreshing
char html[6500] =
"<!DOCTYPE html>\n\
<html>\n\  
<head>\n\  
<meta name='viewport' content='width=device-width, initial-scale=1'>\n\  
<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>\n\  
<style>\n\
body{\n\
background-color: gainsboro;\n\
}\n\
.title{\n\
text-align: center;\n\
background-color: #212121;\n\
color:whitesmoke;\n\
padding: 10px 0px;\n\
margin-bottom: 0px;\n\
font-family: fantasy;\n\
margin-top: 85px;\n\
}\n\
.player-name{\n\
margin-top: 0px;\n\
margin-bottom: 5px;\n\
font-size: 2rem;\n\
}\n\
.container{\n\
width: 762px;\n\
margin: auto;\n\
background-color: whitesmoke;\n\
}\n\
.grid-body{\n\
display: grid;\n\
grid-template-columns: repeat(2,1fr);\n\
}\n\
[class*=\"-container\"]{\n\
background-color: gray;\n\
}\n\
.player-xcontainer{\n\
padding-left: 10px;\n\
border: 1px solid black;\n\
color: whitesmoke;\n\
font-family: monospace;\n\
background-color: #434343;\n\
}\n\
.player-head{\n\
margin-top: 5px;\n\
text-decoration: underline;\n\
}\n\
.low-container{\n\
padding: 14px 10px 14px 25px;\n\
}\n\
.low-container > input{\n\
margin-right: 5px;\n\
}\n\
.btn-reset{\n\
margin-right: 0px !important;\n\
}\n\
[class*=\"btn-\"]{\n\
width: 75px;\n\
height: 45px;\n\
}\n\
.score-container{\n\
grid-column: 1/3;\n\
display: grid;\n\
grid-template-columns: 340px 80px 340px;\n\
background-color: #2a2a2a;\n\
color: white;\n\
}\n\
.author{\n\
grid-column: 1/3;\n\
padding: 7px 5px;\n\
text-align: center;\n\
color: whitesmoke;\n\
background-color: #4c4c4c;\n\
}\n\
.vs-subconts h2{\n\
margin-top: 0px;\n\
margin-bottom: 0px;\n\
margin: auto;\n\
width: 31px;\n\
padding-top: 41px\n\
}\n\
#score-home,\n\
#score-away{\n\
font-size: 4rem;\n\
font-weight: bold;\n\
font-family: fantasy;\n\
}\n\
#score-home{\n\
float:right;\n\
margin-top:12px;\n\
}\n\
#score-away{\n\
float:left;\n\
margin-top:12px;\n\
}\n\
.btnx-score-away,\n\
.btnx-score-home{\n\
height: 40px;\n\
width: 30px;\n\
border-radius: 7px;\n\
padding: 1px 3px;\n\
border: none;\n\
margin-bottom: 8px;\n\
cursor: pointer;\n\
margin-left: 5px;\n\
}\n\
[class*=\"btnx-refresh-\"]{\n\
margin-top: 10px;\n\
height: 87px;\n\
border-radius: 5px;\n\
border: none;\n\
background-color: red;\n\
color: white;\n\
cursor: pointer;\n\
}\n\
.btnx-refresh-away{\n\
margin-right: 15px;\n\
float: right;\n\
}\n\
.btnx-refresh-home{\n\
margin-left: 15px;\n\
float: left;\n\
}\n\
[class*=\"contss-btn\"]{\n\
display: inline-block;\n\
margin-top: 9px;\n\
margin-left: 8px;\n\
}\n\
.contss-btnright{\n\
margin-right: 8px;\n\
width: 118px;\n\
}\n\
.contss-btnleft{\n\
margin-left: 8px;\n\
width: 118px;\n\
}\n\
.contofcont{\n\
float: right;\n\
}\n\
</style>\n\
</head>\n\
<body>\n\
<div class='container'>\n\  
<h1 class='title'>SCOREBOARD</h1>\n\  
<div class='grid-body'>\n\
<div class='home-container'>\n\
<div class='player-xcontainer'>\n\
<div class='player-head'>PLAYER 1</div>\n\
<h2 class='player-name'>HOME</h2>\n\
</div>\n\
<div class='player-xcontainer low-container'>\n\
<input class='home-inputScore' type='number'>\n\
<input class='btn-home-set' type='button' value='SET'>\n\
<input class='btn-home-reset' type='button' value='RESET'>\n\
</div>\n\
</div>\n\
<div class='away-container'>\n\
<div class='player-xcontainer'>\n\
<div class='player-head'>PLAYER 2</div>\n\
<h2 class='player-name'>AWAY</h2>\n\
</div>\n\
<div class='player-xcontainer low-container'>\n\
<input class='away-inputScore' type='number'>\n\
<input class='btn-away-set' type='button' value='SET'>\n\
<input class='btn-away-reset' type='button' value='RESET'>\n\
</div>\n\
</div>\n\
<div class='score-container'>\n\
<span class='home-subconts'>\n\
<button class='btnx-refresh-home' type='button' id='home-refresh' >Refresh</button>\n\   
<span class='contss-btnleft'>\n\
<button class='btnx-score-home' type='button' id='home-minus-1' >-1</button>\n\
<button class='btnx-score-home' type='button' id='home-minus-2' >-2</button>\n\
<button class='btnx-score-home' type='button' id='home-minus-3' >-3</button>\n\
<button class='btnx-score-home' type='button' id='home-plus-1' >+1</button>\n\   
<button class='btnx-score-home' type='button' id='home-plus-2' >+2</button>\n\   
<button class='btnx-score-home' type='button' id='home-plus-3' >+3</button>\n\   
</span>\n\
<span class='score' id='score-home'>0</span>\n\ 
</span>\n\
<span class='vs-subconts'>\n\
<h2>VS</h2>\n\
</span>\n\
<span class='away-subconts'>\n\
<span class='score' id='score-away'>0</span>\n\ 
<span class='contofcont'>\n\
<span class='contss-btnright'>\n\
<button class='btnx-score-away' type='button' id='away-minus-1' >-1</button>\n\
<button class='btnx-score-away' type='button' id='away-minus-2' >-2</button>\n\   
<button class='btnx-score-away' type='button' id='away-minus-3' >-3</button>\n\
<button class='btnx-score-away' type='button' id='away-plus-1' >+1</button>\n\   
<button class='btnx-score-away' type='button' id='away-plus-2' >+2</button>\n\   
<button class='btnx-score-away' type='button' id='away-plus-3' >+3</button>\n\   
</span>\n\     
<button class='btnx-refresh-away' type='button' id='away-refresh' >Refresh</button>\n\   
</span>\n\
</span>\n\
</div>\n\
<div class='author'>created by Jansen Ducusin (https://github.com/senducusin/)</div>\n\
</div>\n\
</div>\n\  
<script>\n\  
$(function() {\n\ 
var btns = ['minus','plus'];\n\
var players = ['home','away'];\n\
$( document ).ready(function() {\n\
$.get(`/req?home-rfrsh=refresh`,function(d,s){\n\
  $.get(`/req?away-rfrsh=refresh`,function(z,x){\n\
    $(`#score-away`).text(z);\n\
  });\n\
$(`#score-home`).text(d);\n\
});\n\
});\n\
for(let z in players){\n\
for(let y in btns){\n\
for(let x = 1; x < 4; x++){\n\
$(`#${players[z]}-${btns[y]}-${x}`).on('click', function(){\n\
$.get(`/req?${players[z]}-${btns[y]}-${x}=score`,function(d,s){\n\ 
$(`#score-${players[z]}`).text(d);\n\ 
});\n\ 
});\n\ 
}\n\
}\n\
$(`#${players[z]}-refresh`).on('click',function(){\n\
$.get(`/req?${players[z]}-rfrsh=refresh`,function(d,s){\n\
$(`#score-${players[z]}`).text(d);\n\
});\n\
});\n\
$(`.btn-${players[z]}-reset`).on('click',function(){\n\
$.get(`/req?${players[z]}-rst=reset`,function(d,s){\n\
$(`#score-${players[z]}`).text(d);\n\
});\n\
});\n\
$(`.btn-${players[z]}-set`).on('click',function(){\n\
let val = $(`.${players[z]}-inputScore`).val();\n\
$.get(`/req?${players[z]}-set-${val}=set`,function(d,s){\n\
$(`.${players[z]}-inputScore`).val(Number(d));\n\
$(`#score-${players[z]}`).text(d);\n\
});\n\
});\n\
}\n\
});\n\
</script>\n\  
</body>\n\  
</html>";

int homeScore = 0;
int awayScore = 0;

void setup() {
  homeScr.setAllLow();
  awayScr.setAllLow();
  
  WiFi.begin(ssid,password);
  Serial.begin(9600);
  
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", handleRoot);
  server.on("/req", handleGPIO);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
   server.handleClient();
}

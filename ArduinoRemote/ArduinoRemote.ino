#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid     = "POCOX3Pro";
const char* password = "0987612345";

ESP8266WebServer server(80);

String output5State = "off";
String output4State = "off";
String buttonStatus = "Очікування натискання кнопки...";

const int output5 = 5;  // GPIO 5
const int output4 = 4;  // GPIO 4
const int buttonPin = 0;  // GPIO 0 for button

bool buttonPressed = false;

void setup() {
  Serial.begin(115200);
  
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/5/on", handleGPIO5On);
  server.on("/5/off", handleGPIO5Off);
  server.on("/4/on", handleGPIO4On);
  server.on("/4/off", handleGPIO4Off);
  server.on("/status", handleStatus);
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command == "5ON") {
      digitalWrite(output5, HIGH);
      output5State = "on";
      Serial.println("LED 1 ON");
    } else if (command == "5OFF") {
      digitalWrite(output5, LOW);
      output5State = "off";
      Serial.println("LED 1 OFF");
    } else if (command == "4ON") {
      digitalWrite(output4, HIGH);
      output4State = "on";
      Serial.println("LED 2 ON");
    } else if (command == "4OFF") {
      digitalWrite(output4, LOW);
      output4State = "off";
      Serial.println("LED 2 OFF");
    }
  }

  if (digitalRead(buttonPin) == LOW && !buttonPressed) {
    buttonPressed = true;
    Serial.println("Button pressed");

    if (digitalRead(output5) == LOW && digitalRead(output4) == LOW) {
      digitalWrite(output5, HIGH);
      digitalWrite(output4, HIGH);
      output5State = "on";
      output4State = "on";
      buttonStatus = "Користувач за допомогою кнопки увімкнув світлодіоди";
      Serial.println("Both LEDs turned ON");
    } else {
      digitalWrite(output5, LOW);
      digitalWrite(output4, LOW);
      output5State = "off";
      output4State = "off";
      buttonStatus = "Користувач за допомогою кнопки вимкнув світлодіоди";
      Serial.println("Both LEDs turned OFF");
    }
  }

  if (digitalRead(buttonPin) == HIGH && buttonPressed) {
    buttonPressed = false;
  }
}

void handleRoot() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<link rel=\"icon\" href=\"data:,\">";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;} ";
  html += ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px; ";
  html += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;} ";
  html += ".button2 {background-color: #77878A;}</style>";
  html += "<script>";
  html += "function updateStatus() {";
  html += "  fetch('/status')";
  html += "    .then(response => response.json())";
  html += "    .then(data => {";
  html += "      document.getElementById('buttonStatus').innerHTML = data.buttonStatus;";
  html += "      document.getElementById('led5').innerHTML = 'GPIO 5 - State ' + data.output5State;";
  html += "      document.getElementById('led4').innerHTML = 'GPIO 4 - State ' + data.output4State;";
  html += "      document.getElementById('btn5').className = data.output5State === 'on' ? 'button button2' : 'button';";
  html += "      document.getElementById('btn5').innerHTML = data.output5State === 'on' ? 'OFF' : 'ON';";
  html += "      document.getElementById('btn5').href = data.output5State === 'on' ? '/5/off' : '/5/on';";
  html += "      document.getElementById('btn4').className = data.output4State === 'on' ? 'button button2' : 'button';";
  html += "      document.getElementById('btn4').innerHTML = data.output4State === 'on' ? 'OFF' : 'ON';";
  html += "      document.getElementById('btn4').href = data.output4State === 'on' ? '/4/off' : '/4/on';";
  html += "    });";
  html += "}";
  html += "setInterval(updateStatus, 1000);";
  html += "</script>";
  html += "</head>";
  html += "<body onload=\"updateStatus()\">";
  html += "<h1>ESP8266 Web Server</h1>";
  html += "<p id='led5'>GPIO 5 - State " + output5State + "</p>";
  html += "<p><a id='btn5' href='/5/" + String(output5State == "off" ? "on" : "off") + "' class='button" + String(output5State == "on" ? " button2" : "") + "'>" + String(output5State == "off" ? "ON" : "OFF") + "</a></p>";
  html += "<p id='led4'>GPIO 4 - State " + output4State + "</p>";
  html += "<p><a id='btn4' href='/4/" + String(output4State == "off" ? "on" : "off") + "' class='button" + String(output4State == "on" ? " button2" : "") + "'>" + String(output4State == "off" ? "ON" : "OFF") + "</a></p>";
  html += "<p id='buttonStatus'>" + buttonStatus + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}


void handleStatus() {
  String json = "{";
  json += "\"buttonStatus\":\"" + buttonStatus + "\",";
  json += "\"output5State\":\"" + output5State + "\",";
  json += "\"output4State\":\"" + output4State + "\"";
  json += "}";
  server.send(200, "application/json", json);
}

void handleGPIO5On() {
  digitalWrite(output5, HIGH);
  output5State = "on";
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleGPIO5Off() {
  digitalWrite(output5, LOW);
  output5State = "off";
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleGPIO4On() {
  digitalWrite(output4, HIGH);
  output4State = "on";
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleGPIO4Off() {
  digitalWrite(output4, LOW);
  output4State = "off";
  server.sendHeader("Location", "/");
  server.send(303);
}
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = "BonnAgile";
const char *text_html = "text/html";
const char *markup = "<h1>ESP8266 Web Server</h1><p>Internal LED <a href=\"ON\"><button>ON</button></a>&nbsp;<a href=\"OFF\"><button>OFF</button></a></p>";

IPAddress localIp(192,168,10,1);
IPAddress gateway(192,168,10,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

void handleRoot() {
  sendResponse();
}

void handleOn() {
  digitalWrite(LED_BUILTIN, LOW);
  sendResponse();
}

void handleOff() {
  digitalWrite(LED_BUILTIN, HIGH);
  sendResponse();
}

void sendResponse() {
  server.send(200, text_html, markup);
}

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.println("Configuring internal led.");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("Configuring access point.");
  WiFi.softAPConfig(localIp, gateway, subnet);
  WiFi.softAP(ssid);

  server.on("/", handleRoot);
  server.on("/ON", handleOn);
  server.on("/OFF", handleOff);
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
}

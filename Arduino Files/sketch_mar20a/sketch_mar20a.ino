#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

const char* ssid = "your_SSID"; // replace with your WiFi SSID
const char* password = "your_PASSWORD"; // replace with your WiFi password

AsyncWebServer server(80);

const int ledPin = 2; // replace with the pin number for your LED bulb
bool isLedOn = false; // initial state of the LED bulb

void setup() {
  // initialize the LED bulb pin as an output
  pinMode(ledPin, OUTPUT);

  // connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // set up the server routes
  server.on("/toggle-led", HTTP_POST, handleToggleLed);

  // start the server
  server.begin();
}

void handleToggleLed(AsyncWebServerRequest *request) {
  // parse the incoming JSON data
  StaticJsonDocument<200> doc;
  deserializeJson(doc, request->getParam("plain")->value().c_str());
  bool newIsLedOn = doc["isOn"];

  // update the state of the LED bulb if it has changed
  if (newIsLedOn != isLedOn) {
    isLedOn = newIsLedOn;
    digitalWrite(ledPin, isLedOn ? HIGH : LOW);
  }

  // send a response back to the client
  request->send(200, "application/json", "{\"success\": true}");
}

void loop() {
  // do nothing
}

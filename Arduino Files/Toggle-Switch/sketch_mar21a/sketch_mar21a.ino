#include <ESPAsyncWebServer.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>

const char* ssid = "SLT_FIBRE";
const char* password = "638080338";
const int ledPin = D4;
AsyncWebServer server(80);

void handleToggleState(AsyncWebServerRequest *request) {
  if (request->hasParam("state")) {
    String state = request->getParam("state")->value();
    // Do something with the state here
    request->send(200, "text/plain", "State received");
  } else {
    request->send(400, "text/plain", "Missing state parameter");
  }
}

void setup() {
  // Set up SPIFFS here
  server.on("/toggle", HTTP_POST, handleToggleState);
  server.begin();


   Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin()){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());


// Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });
  
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });
 server.begin();
 }

void loop() {
  // Handle other tasks here
}

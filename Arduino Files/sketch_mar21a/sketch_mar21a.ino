// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>
#include<ArduinoJson.h>


// Replace with your network credentials
const char* ssid = "SLT_FIBRE";
const char* password = "638080338";

// Set LED GPIO
const int ledPin = D4;
// Stores LED state
String ledState;
bool isLedOn = false; // initial state of the LED bulb

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


/*void handleRequest(AsyncWebServerRequest *request) {
  Serial.println("Hii");
  // Retrieve the value of a parameter named "paramName"
  String paramValue = request->arg("paramName");
Serial.println(paramValue);
   digitalWrite(ledPin, paramValue == "on" ? HIGH : LOW);
  // Send the parameter value back to the client
  request->send(200, "text/plain", "Parameter value: " + paramValue);
}*/

void handle_on(AsyncWebServerRequest *request) {
  ledState = HIGH;
  digitalWrite(ledPin,HIGH);
}
void handle_off(AsyncWebServerRequest *request) {
  ledState = LOW;
  digitalWrite(ledPin,LOW);
}
 
void setup(){
  // Serial port for debugging purposes
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

  // Handle the toggle switch control
    server.on("/bulbon",HTTP_GET,handle_on);
    
    server.on("/bulboff",HTTP_GET,handle_off);
   
    Serial.println("Hii");


  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
 //server.handleClient();
 
}

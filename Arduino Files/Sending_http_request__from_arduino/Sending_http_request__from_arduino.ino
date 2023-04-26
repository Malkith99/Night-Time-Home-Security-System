// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
#include<ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Servo.h> 

// Replace with your network credentials
const char* ssid = "Redmi Note 9S";
const char* password = "12345678";
// Set static IP address

IPAddress staticIP(192, 168, 92, 130); // replace with desired IP address
IPAddress gateway(192, 168, 92, 12); // replace with your gateway IP address
IPAddress subnet(255, 255, 255, 0);

// Set  GPIO
int pirValue; // Place to store read PIR Value
//int ldrValue; // Place to store read LDR Value

//int relayPin=D7;
// Stores switch state

bool isActivate = false; // initial state of the System

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);


void handle_on(AsyncWebServerRequest *request) {
  //ledState = HIGH;
  isActivate = HIGH;

  //digitalWrite(ledPin1,HIGH);
}
void handle_off(AsyncWebServerRequest *request) {
  //ledState = LOW;
  isActivate = LOW;
  //digitalWrite(ledPin1,LOW);

}

Servo pro;
int counter = 0;

void setup(){
  pinMode(D0, OUTPUT);   //LED Red 
  pinMode(D1, INPUT);  //  PIR Sensor
  pinMode(D2, OUTPUT);   //LED Green 
  pinMode(D3, OUTPUT); // declare Buzzer as output
  pinMode(D4, INPUT);   //LDR Sensor 
  
  //pinMode(D7,OUTPUT);

  pro.attach(D6);//Servo Motor
  
  // Serial port for debugging purposes
  Serial.begin(115200);
  

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
  
  // Set static IP address
  WiFi.config(staticIP, gateway, subnet);
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
    server.on("/switchon",HTTP_GET,handle_on);
    server.on("/switchoff",HTTP_GET,handle_off);

  Serial.println("Hii");
  server.begin();
  Serial.println("HTTP server started");

}


void loop() {
       if (isActivate == HIGH)    
      {
        //ldrValue=digitalRead(D4);
       // if(ldrValue){
        digitalWrite(D2, HIGH);
        digitalWrite(D0, LOW);
        //digitalWrite(D7, HIGH);
         getPirValue();
        /*}else{
         Serial.println("Environment is not Dark");
        }*/
        
      }else{
         digitalWrite(D2, LOW);
         digitalWrite(D7, LOW);
      }
}

void getPirValue(void)        //Get PIR Data
  {
   pirValue = digitalRead(D1);
   Serial.println(pirValue);
    if (pirValue) 
     { 
        Serial.println("Motion detected");
        digitalWrite(D0, HIGH);
        digitalWrite(D2, LOW);
        tone(D3, 10000,800);
        delay(1000); 

        //Triggering of the Camera
            if (counter < 3) { 
  
                for (int angle = 180; angle >= 100; angle -= 80) { 
                pro.write(angle); 
               delay(1); 
              } 
              delay(1000);
               for (int angle = 100; angle <= 180; angle += 80) { 
                pro.write(angle); 
                delay(1); 
              } 
              delay(1000);
              counter++; 

            } 
            delay(1000);
            counter=0;
         //String alertMsg = "<script>alert('Motion detected!');</script>";
        //server.send(200, "text/html", alertMsg);

    // Make HTTP GET request
       // WiFiClient wifiClient;
       // HTTPClient http;
        //http.begin(wifiClient, "http://192.168.1.130/alert");
        //http.GET();
       // http.end();

     }
  }

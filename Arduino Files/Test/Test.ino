#define BLYNK_TEMPLATE_ID "TMPLc8xony1z"
#define BLYNK_TEMPLATE_NAME "Security System"
#define BLYNK_AUTH_TOKEN "Wh4gTu7qpujmajtg99wpFlx2LTgT5anz"

//Include the library files
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_AUTH_TOKEN "Wh4gTu7qpujmajtg99wpFlx2LTgT5anz" //Enter your blynk auth token

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SLT_FIBRE";//Enter your WIFI name
char pass[] = "638080338";//Enter your WIFI password

#define pirPin 5                // Input for HC-S501
int pirValue;                   // Place to store read PIR Value
int pinValue;                   //Variable to read virtual pin

//Get the button value
BLYNK_WRITE(V0) {
  //digitalWrite(D2, param.asInt());
  pinValue = param.asInt(); 
}

void setup() {
  //Set the LED pin as an output pin
  //pinMode(D2, OUTPUT);
   Serial.begin(115200);
   //delay(10);
  pinMode(D1, INPUT);  //  PIR Sensor
  pinMode(D3, OUTPUT); // declare Buzzer as output
  pinMode(D0, OUTPUT);   //LED Red 
  pinMode(D2, OUTPUT);   //LED Green 
  //Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  //Run the Blynk library
      if (pinValue == HIGH)    
      {
        digitalWrite(D2, HIGH);
        digitalWrite(D0, LOW);
        getPirValue();
      }else{
         digitalWrite(D2, LOW);
      }
  Blynk.run();
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
      //Blynk.notify("Motion detected");  
     }
  }

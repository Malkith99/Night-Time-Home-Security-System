#define BLYNK_TEMPLATE_ID "TMPLc8xony1z"
#define BLYNK_TEMPLATE_NAME "Security System"
#define BLYNK_AUTH_TOKEN "qB9NmtDUU-c3g02vV4-Nzs1xVCl1dPE4"

  
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_AUTH_TOKEN "qB9NmtDUU-c3g02vV4-Nzs1xVCl1dPE4" //Enter your blynk auth token

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SLT_FIBRE";//Enter your WIFI name
char pass[] = "638080338";//Enter your WIFI password

//Get the button value
BLYNK_WRITE(V0) {
  digitalWrite(D0, param.asInt());
}

void setup() {
  //Set the LED pin as an output pin
  pinMode(D0, OUTPUT);
  //Initialize the Blynk library
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  //Run the Blynk library
  Blynk.run();
}

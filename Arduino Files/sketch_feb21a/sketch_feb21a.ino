//int LED = D2;       
//int Buzzer = D3   
//int SENSOR_OUTPUT_PIN = D1;

void setup() {

  pinMode(D1, INPUT);  //
  pinMode(D3, OUTPUT); // declare Buzzer as output
  pinMode(D2, OUTPUT);   //LED        

  Serial.begin(9600);

}

void loop() {

 int sensorvalue = digitalRead(D1);

  Serial.println(sensorvalue);
  
  if (sensorvalue== HIGH) {
 
   digitalWrite(D2, HIGH);
   tone(D3, 15000,800);
  Serial.println("Motion detected!");
    delay(500);
}

  else {

   digitalWrite(D2, LOW);
   
  }
}

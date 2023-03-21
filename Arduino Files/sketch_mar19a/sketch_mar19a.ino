#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>

const char* ssid = "SLT_FIBRE";
const char* password = "638080338";

ESP8266WebServer server(80);

void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  server.streamFile(file, "text/html");
  file.close();
}

/*void handleNotFound(){
  File file = SPIFFS.open("/404.html", "r");
  server.streamFile(file, "text/html");
  file.close();
}*/

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  if (!SPIFFS.begin()) {
    Serial.println("Failed to initialize SPIFFS");
    return;
  }
  Serial.println("SPIFFS initialized");

  server.on("/", handleRoot);
 // server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("Web server started");
  
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}

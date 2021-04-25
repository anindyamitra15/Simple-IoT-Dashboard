#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>
#include "webpage.h" //includes the webpage

ESP8266WiFiMulti multiAP;;
AsyncWebServer server(80);//serves at port 80 (default)

const char* ssid1 = "WiFiAP";
const char* pass1 = "12345678";

#define LED1 4  //only for toggle (Pin D2)
#define LED2 5  //for slider control (Pin D1)
#define LED_BUILTIN 2

void setup() {
  pinMode (LED_BUILTIN, OUTPUT);
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  Serial.begin(115200);
  multiAP.addAP(ssid1, pass1);//passes the credentials
  WiFi.mode(WIFI_STA);
  Serial.println("\nConnecting: ");
  //keeps looping till WiFi gets connected
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, LOW);
    delay(400);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(400);
  }
  Serial.print("\nConnected: ");
  Serial.println(WiFi.localIP());//prints the connection IP


  // Route for web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", indexPage); //hosts the page on '/' route
  });

  //Route for the values  
  server.on("/switch", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (request->hasArg("data")) { // if data value is found
      bool arg = request->arg("data").equals("true");
      digitalWrite(LED1, arg);
      Serial.print("data: ");
      Serial.println(arg);
      request->send(200, "text/html", "Success");
    }
    else if(request->hasArg("slider")) { // if slider value is found
      //takes the number sent by the request
      int arg = request->arg("slider").toInt();
      analogWrite(LED2, arg);
      Serial.print("slider: ");
      Serial.println(arg);
      request->send(200, "text/html", "Success");
    }
    else{
      request->send(400, "text/html", "Bad Request");
    }
  });

  // Start server
  server.begin();

}

void loop() {}

//Havo Smart Technology
//Develop : Muhammad Ikhwan Fathulloh
//Stack : HTML, CSS, Javascript, Bootstrap 5, Websocket, ESP8266/32, JSON, Arduino

//Check Board ESP
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif

//Library WifiManager
#include<WiFiManager.h>  

//Library Websocket and ArduinoJson
#include <WebSocketsServer.h>
#include <Ticker.h>
#include <ArduinoJson.h>

//Library On The Air
#include <AsyncElegantOTA.h>

//Page HTML
#include "Dashboard.h"
#include "NotFound.h"

//SSID and Password
const char* ssid = "ESP32";
const char* password = "1sampai100";

//Pin Kontak
#define Kontak1 13
#define Kontak2 12
#define Kontak3 14
#define Kontak4 27

#include <ESPAsyncWebServer.h>

AsyncWebServer server(80); // server port 80
WebSocketsServer websockets(81);

void send_sensor();

Ticker timer;

//Page not found
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/html", notfoundpage);
}

//Websocket Event Kontak
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) 
  {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);

        // send message to client
        websockets.sendTXT(num, "Connected from server");
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      String message = String((char*)( payload));
      Serial.println(message);

      
     DynamicJsonDocument doc(200);
    // deserialize the data
    DeserializationError error = deserializeJson(doc, message);
    // parse the parameters we expect to receive (TO-DO: error handling)
      // Test if parsing succeeds.
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  //Check status contact with parsing JSON
  int Kontak1_status = doc["Kontak1"];
  int Kontak2_status = doc["Kontak2"];
  int Kontak3_status = doc["Kontak3"];
  int Kontak4_status = doc["Kontak4"];

  //Contact
  digitalWrite(Kontak1,Kontak1_status);
  digitalWrite(Kontak2,Kontak2_status);
  digitalWrite(Kontak3,Kontak3_status);
  digitalWrite(Kontak4,Kontak4_status);
  }
}

void setup(void)
{
  Serial.begin(115200);
  pinMode(Kontak1,OUTPUT);
  pinMode(Kontak2,OUTPUT);
  pinMode(Kontak3,OUTPUT);
  pinMode(Kontak4,OUTPUT);

  //WifiManager  
  WiFiManager wifiManager;  

  //Access Point  
  wifiManager.autoConnect("ConnectHavo","password");  
  Serial.println("Connected.....");  
    
  if (MDNS.begin("havo")) { //havo.local/
    Serial.println("MDNS responder started");
  }
  
  //Dashboard Page
  server.on("/", [](AsyncWebServerRequest * request)
  { 
   
  request->send_P(200, "text/html", webpage);
  });

  server.onNotFound(notFound);
  AsyncElegantOTA.begin(&server); // Start ElegantOTA
  server.begin();  // it will start webserver
  websockets.begin();
  websockets.onEvent(webSocketEvent);
  timer.attach(2,send_sensor);
}

void loop(void)
{
 // Websocket
 websockets.loop();
}

//Sensor Realtime
void send_sensor()
{
   // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  String title = "Hello word";
  int counter = 0;
  
  for(int i = 0; i <= 100; i++){
    counter = i;
    // JSON_Data = {"title":title,"counter":counter}
    String JSON_Data = "{\"title\":";
           JSON_Data += "\"";
           JSON_Data += title;
           JSON_Data += "\"";
           JSON_Data += ",\"counter\":";
           JSON_Data += counter;
           JSON_Data += "}";
    Serial.println(JSON_Data);     
    websockets.broadcastTXT(JSON_Data);
    delay(1000);
  }
}

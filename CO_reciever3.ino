#include <esp_now.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include <Arduino_JSON.h>
#include "website.h"
#include "FS.h"
#include "SPIFFS.h"


// Replace with your network credentials (STATION)  2 v 2
const char* ssid = "-------";
const char* password = "--------";

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message 
{
  int id;
  float co;
  float max_co;
  unsigned int readingId;
} struct_message;

struct_message incomingReadings;
bool isRecordingPaused = false;

JSONVar board;

AsyncWebServer server(80);
AsyncEventSource events("/events");

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) { 
  // Copies the sender mac address to a string
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  

  board["id"] = incomingReadings.id;
  board["carbon_monoxide"] = incomingReadings.co;
  board["max_carbon_monoxide"] = incomingReadings.max_co;
  board["readingId"] = String(incomingReadings.readingId);
  String jsonString = JSON.stringify(board);
  events.send(jsonString.c_str(), "new_readings", millis());
  
  Serial.printf("Board ID %u: %u bytes\n", incomingReadings.id, len);
  Serial.printf("CO value: %4.2f \n", incomingReadings.co);  
  Serial.printf("Max CO value: %4.2f \n", incomingReadings.max_co);
  Serial.printf("readingID value: %d \n", incomingReadings.readingId);
  Serial.println();
}

void setup() 
{
  Serial.begin(115200);
  // Initialize Serial Monitor
  Serial.println();
  Serial.print("ESP Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
if (!SPIFFS.begin(true)) {
  Serial.println("An error has occurred while mounting SPIFFS");
  return;



  server.on("/pause", HTTP_POST, [](AsyncWebServerRequest *request) {
  isRecordingPaused = true;
  request->send(200, "text/plain", "Data recording paused.");
});

server.on("/resume", HTTP_POST, [](AsyncWebServerRequest *request) {
  isRecordingPaused = false;
  request->send(200, "text/plain", "Data recording resumed.");
});

}

  // Set the device as a Station and Soft Access Point simultaneously
  WiFi.mode(WIFI_AP_STA);
  server.on("/data.csv", HTTP_GET, [](AsyncWebServerRequest *request) {
  request->send(SPIFFS, "/data.csv", "text/csv");
});

  // Set device as a Wi-Fi Station
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Setting as a Wi-Fi Station..");
  }
  Serial.print("Station IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Wi-Fi Channel: ");
  Serial.println(WiFi.channel());

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to get recv packer info
  esp_now_register_recv_cb(OnDataRecv);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    request->send_P(200, "text/html", index_html);
  });
   
  events.onConnect([](AsyncEventSourceClient *client)
  {
    if(client->lastId())
    {
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);
  server.begin();
}
 
void loop() 
{
  static unsigned long lastEventTime = millis();
  static const unsigned long EVENT_INTERVAL_MS = 5000;
  if ((millis() - lastEventTime) > EVENT_INTERVAL_MS) 
  {
    events.send("ping",NULL,millis());
    lastEventTime = millis();
  }
}

#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

// Set the Board ID
#define BOARD_ID 1

// MAC Address of the receiver 
uint8_t broadcastAddress[] = {0xE0, 0x5A, 0x1B, 0x5F, 0x5D, 0x40};

// Structure used to send data
typedef struct struct_message 
{
  int id;
  float co;
  float max_co;
  unsigned int readingId;
} struct_message;

// Create a struct_message called myData
struct_message myData;

unsigned long previousMillis = 0;   // Stores last time temperature was published
const long interval = 1000;        // Interval at which to publish sensor readings

unsigned int readingId = 0;
float max_co = 0;

// My SSID
constexpr char WIFI_SSID[] = "SM-G950UBA3";

int32_t getWiFiChannel(const char *ssid) 
{
  if (int32_t n = WiFi.scanNetworks()) {
      for (uint8_t i=0; i<n; i++) {
          if (!strcmp(ssid, WiFi.SSID(i).c_str())) {
              return WiFi.channel(i);
          }
      }
  }
  return 0;
}

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) 
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup()
{
  Serial.begin(115200); // Set serial baud rate to 115200 bps
  
  Serial.println("Started");
  Serial.print("");
 
  // Set device as a Wi-Fi Station and set channel
  WiFi.mode(WIFI_STA);

  int32_t channel = getWiFiChannel(WIFI_SSID);

  WiFi.printDiag(Serial); // Uncomment to verify channel number before
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
  esp_wifi_set_promiscuous(false);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }
}
 
void loop() 
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) 
  {
    // Save the last time a new reading was published
    previousMillis = currentMillis;
    //Set values to send
    // Set values to send
    myData.id = BOARD_ID;

    // THIS IS THE ONLY THING THAT NEEDS TO BE CHANGED
    myData.co = float(analogRead(34)) / 100;
    //
    
    if (myData.max_co < myData.co)
    {
      myData.max_co = myData.co;
    }

    myData.readingId = readingId++;
    Serial.println(myData.co);// Print the value of CO to serial port for verification
     
    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    if (result == ESP_OK) 
    {
      Serial.println("Sent with success");
    }
    else 
    {
      Serial.println("Error sending the data");
    }
  }
}

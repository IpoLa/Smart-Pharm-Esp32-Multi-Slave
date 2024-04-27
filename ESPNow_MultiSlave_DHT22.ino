// Include Libraries
#include <WiFi.h>
#include <esp_now.h>
#include "DHT22.h"
#define pinDATA 23
DHT22 dht22(pinDATA); 

void formatMacAddress(const uint8_t *macAddr, char *buffer, int maxLength)
// Formats MAC Address
{
  snprintf(buffer, maxLength, "%02x:%02x:%02x:%02x:%02x:%02x", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
}


//void receiveCallback(const uint8_t *macAddr, const uint8_t *data, int dataLen)
//// Called when data is received
//{
//  // Only allow a maximum of 250 characters in the message + a null terminating byte
//  char buffer[ESP_NOW_MAX_DATA_LEN + 1];
//  int msgLen = min(ESP_NOW_MAX_DATA_LEN, dataLen);
//  strncpy(buffer, (const char *)data, msgLen);
//
//  // Make sure we are null terminated
//  buffer[msgLen] = 0;
//
//  // Format the MAC address
//  char macStr[18];
//  formatMacAddress(macAddr, macStr, 18);
//
//  // Send Debug log message to the serial port
//  Serial.printf("Received message from: %s - %s\n", macStr, buffer);
//
//  
//  digitalWrite(STATUS_LED, ledOn);
//}


void sentCallback(const uint8_t *macAddr, esp_now_send_status_t status)
// Called when data is sent
{
  char macStr[18];
  formatMacAddress(macAddr, macStr, 18);
  Serial.print("Last Packet Sent to: ");
  Serial.println(macStr);
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void broadcast(const String &message)
// Emulates a broadcast
{
  // Broadcast a message to every device in range
  uint8_t broadcastAddress[] = {0xAC, 0x67, 0xB2, 0x37, 0x15, 0x48};
// Master AC:67:B2:37:15:48
  esp_now_peer_info_t peerInfo = {};
  memcpy(&peerInfo.peer_addr, broadcastAddress, 6);
  if (!esp_now_is_peer_exist(broadcastAddress))
  {
    esp_now_add_peer(&peerInfo);
  }
  // Send message
  esp_err_t result = esp_now_send(broadcastAddress, (const uint8_t *)message.c_str(), message.length());

  // Print results to serial monitor
  if (result == ESP_OK)
  {
    Serial.println("Broadcast message success");
  }
  else if (result == ESP_ERR_ESPNOW_NOT_INIT)
  {
    Serial.println("ESP-NOW not Init.");
  }
  else if (result == ESP_ERR_ESPNOW_ARG)
  {
    Serial.println("Invalid Argument");
  }
  else if (result == ESP_ERR_ESPNOW_INTERNAL)
  {
    Serial.println("Internal Error");
  }
  else if (result == ESP_ERR_ESPNOW_NO_MEM)
  {
    Serial.println("ESP_ERR_ESPNOW_NO_MEM");
  }
  else if (result == ESP_ERR_ESPNOW_NOT_FOUND)
  {
    Serial.println("Peer not found.");
  }
  else
  {
    Serial.println("Unknown error");
  }
}



void temperature() {
  delay(2000);

  Serial.println(dht22.debug()); //optionnal

  float t = dht22.getTemperature();
  float h = dht22.getHumidity();

  if (dht22.getLastError() != dht22.OK) {
    Serial.print("last error :");
    Serial.println(dht22.getLastError());
  }

  Serial.print("h=");Serial.print(h,1);Serial.print("\t");
  Serial.print("t=");Serial.println(t,1);
  Serial.println(dht22.debug()); //optionnal

  if (dht22.getLastError() != dht22.OK) {
    Serial.print("last error :");
    Serial.println(dht22.getLastError());
  }

  Serial.print("h=");Serial.print(h,1);Serial.print("\t");
  Serial.print("t=");Serial.println(t,1);
  delay(2000);
  
//  broadcast("Temperature : " + String(t) + " Humidity : " + String(h));
  broadcast(String(t));
}

void setup()
{

  // Set up Serial Monitor
  
  Serial.begin(115200);
  delay(1000);
  

  // Set ESP32 in STA mode to begin with
  WiFi.mode(WIFI_STA);
  Serial.println("ESP-NOW Broadcast Demo");

  // Print MAC address
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  // Disconnect from WiFi
  WiFi.disconnect();

  // Initialize ESP-NOW
  if (esp_now_init() == ESP_OK)
  {
    Serial.println("ESP-NOW Init Success");
//    esp_now_register_recv_cb(receiveCallback);
    esp_now_register_send_cb(sentCallback);
  }
  else
  {
    Serial.println("ESP-NOW Init Failed");
    delay(3000);
    ESP.restart();
  }
}

void loop()
{
 temperature(); 
 delay(500);
}


// Master : AC:67:B2:37:15:48
// Slave DHT : 9c:9c:1f:eb:00:98
// Slave LDR : 94:e6:86:12:26:b4

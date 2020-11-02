#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiServer.h>
#include <LWiFiClient.h>
#define WIFI_AP "ORL"
#define WIFI_PASSWORD "orl_india"
#define WIFI_AUTH LWIFI_WPA
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "74609CFWVEVMJNRI";
const int updateThingSpeakInterval = 16 * 1000;      // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)long lastConnectionTime = 0; 
boolean lastConnected = false;
int failedCounter = 0;
LWiFiClient client;
void setup()
{
  LWiFi.begin();
  Serial.begin(9600);  // keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    delay(1000);
  }
  startWifi(); 
}
void loop()
{
  String analogValue0 = String(analogRead(A0), DEC);
  String analogValue1 = String(analogRead(A1), DEC);
  String analogValue2 = String(analogRead(A2), DEC);
  // Print Update Response to Serial Monitor
  if (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }  // Disconnect from ThingSpeak
  if (!client.connected() && lastConnected)
  {
    Serial.println("...disconnected");
    Serial.println();
    
    client.stop();
  }
  
  // Update ThingSpeak
  if(!client.connected())
  {
    updateThingSpeak("field1="+analogValue0+"&field2="+analogValue1+"&field3="+analogValue2);
  }
  
  // Check if Arduino Ethernet needs to be restarted
  if (failedCounter > 3 ) {startWifi();}
  
  lastConnected = client.connected();
}
void updateThingSpeak(String tsData)
{
  if (client.connect(thingSpeakAddress, 80))
  {         
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);
   
    
    if (client.connected())
    {
      Serial.println("Connecting to ThingSpeak...");
      Serial.println();
      
      failedCounter = 0;
    }
    else
    {
      failedCounter++;
  
      Serial.println("Connection to ThingSpeak failed ("+String(failedCounter, DEC)+")");   
      Serial.println();
    }
    
  }
  else
  {
    failedCounter++;
    
    Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");   
    Serial.println();
    
  }
}
void startWifi()
{
  
  client.stop(); 
  Serial.println("Connecting Arduino to network...");
  Serial.println();
  delay(1000);
    
}

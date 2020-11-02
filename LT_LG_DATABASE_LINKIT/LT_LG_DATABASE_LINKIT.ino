#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiServer.h>
#include <LWiFiClient.h>
#include <LGPS.h>

#define WIFI_AP "ORL"
#define WIFI_PASSWORD "orl_india"
#define WIFI_AUTH LWIFI_WPA

const int updateThingSpeakInterval = 16 * 1000;      // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)long lastConnectionTime = 0; 
boolean lastConnected = false;
int failedCounter = 0;
String data;
LWiFiClient client;
gpsSentenceInfoStruct info;
char buff[256];
char buf[20];
char lt[20];
char lg[20];

double latitude;
double longitude;
  


void setup()
{
  LWiFi.begin();
  Serial.begin(9600); 
  LGPS.powerOn();
  Serial.println("LGPS Power on, and waiting ..."); 
  delay(3000);
   // keep retrying until connected to AP
  Serial.println("Connecting to AP");
  while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    delay(1000);
  }
  startWifi(); 
}
void loop()
{ 
   Serial.println("GPS READING..."); 
   LGPS.getData(&info);
   parseGPRMC((const char*)info.GPRMC);
   delay(2000);
   Serial.print("LT:");
   Serial.print(lt);
   Serial.print(",LG:");
   Serial.println(lg);
   
   data = "lt_value="+String(lt)+"&lg_value="+String(lg);
   data += "\r\n\r\n";
   
   if (client.connect("192.168.1.8",80))
   { // REPLACE WITH YOUR SERVER ADDRESS
    client.println("POST /LKIT/linkit.php HTTP/1.1"); 
    Serial.println("POST /LKIT/linkit.php HTTP/1.1"); 
    client.println("Host:192.168.1.8"); // SERVER ADDRESS HERE TOO
    Serial.println("Host:192.168.1.8"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded");
    Serial.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: ");
    Serial.print("Content-Length: "); 
    client.println(data.length()); 
    Serial.println(data.length()); 
    client.println(); 
    client.print(data);
    delay(1000);
    Serial.println(data); 
  } 

  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }

  delay(3000); // WAIT FIVE MINUTES BEFORE SENDING AGAIN
}

void startWifi()
{
  
  client.stop(); 
  Serial.println("Connecting Arduino to network...");
  Serial.println();
  delay(1000);
    
}

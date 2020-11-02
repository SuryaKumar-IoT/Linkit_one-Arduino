//Put your variable key in "idvariable"

//and put your token key in "token" 
#include <LTask.h>
#include <LWiFi.h>
#include <LWiFiClient.h>
#define WIFI_AP "ORL"
#define WIFI_PASSWORD "orl_india"
#define WIFI_AUTH LWIFI_WPA  // choose from LWIFI_OPEN, LWIFI_WPA, or LWIFI_WEP according to you WiFi AP configuration

LWiFiClient client;

String idvariable = "572c5f5876254247c4bc7a32";
String token = "qGu3yZn8PCtm1t6Nu297PhSjTo6DF5";

void setup() {
    // Open serial communications and wait for port to open:
     LWiFi.begin();
     Serial.begin(9600);
     
     Serial.println("connecting...");
     while (0 == LWiFi.connect(WIFI_AP, LWiFiLoginInfo(WIFI_AUTH, WIFI_PASSWORD)))
  {
    delay(1000);
  }
   }

void loop()
   {
     int value = analogRead(A0);
     save_value(String(value));
   }

void save_value(String value)
   {
     // if you get a connection, report back via serial:
     int num=0;
     String var = "{\"value\":"+ String(value) + "}";
     num = var.length();
     delay(10000);
     if(client.connect("things.ubidots.com", 80))
     {
       Serial.println("connected");    // New lines according to ubidots support:       
       client.println("POST /api/v1.6/variables/"+idvariable+"/values HTTP/1.1");
       Serial.println("POST /api/v1.6/variables/"+idvariable+"/values HTTP/1.1");
       client.println("Content-Type: application/json");
       Serial.println("Content-Type: application/json");
       client.println("Content-Length: "+String(num));
       Serial.println("Content-Length: "+String(num));
       client.println("X-Auth-Token: "+token);
       Serial.println("X-Auth-Token: "+token);
       client.println("Host: things.ubidots.com\n");
       Serial.println("Host: things.ubidots.com\n");
       client.print(var);
       Serial.print(var+"\n");
     }
     else
     {
       // if you didn't get a connection to the server:
       Serial.println("connection failed");
     }

   if (!client.connected())
     {
       Serial.println();
       Serial.println("disconnecting.");
       client.stop();
     }

    if (client.available())
     {
       char c = client.read();
       Serial.print(c);
     }
     client.flush();
     client.stop();

}

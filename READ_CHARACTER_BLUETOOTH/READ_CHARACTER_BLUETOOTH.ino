#include <LBT.h>
#include <LBTServer.h>
#define SPP_SVR "LINKIT ONE" 
char buf[15];
int read_size = 0;
void setup()
{
  Serial.begin(9600);
  bool success = LBTServer.begin((uint8_t*)SPP_SVR);
  if( !success )
  {
      Serial.print("Cannot begin Bluetooth");
      delay(0xffffffff);
  }
  else
  {
      Serial.println("Server created");
  }
  bool connected = LBTServer.accept(1800);
 
  if( !connected )
  {
      Serial.println("No connection");
      delay(0xffffffff);
  }
  else
  {
      Serial1.println("Connected\n");
  }
}
void loop()
{
   if(LBTServer.available())
   {
       LBTServer.readBytes((uint8_t*)buf,12);
       Serial.println(buf);
       if(buf[0]=='A')
       {
          Serial.println("FORWARD");
       }
       else if(buf[0]=='B')
       {
          Serial.println("BACKWARD");
       }
       else if(buf[0]=='L')
       {
          Serial.println("LEFT");
       }
       else if(buf[0]=='R')
       {
          Serial.println("RIGHT");
       }
       else if(buf[0]=='S')
       {
          Serial.println("STOP");
       }
   }
   delay(2000);
}


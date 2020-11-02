#include <LTask.h>
#include <LGSM.h>

void setup()
{
    Serial.begin(9600);
    
    while(!LSMS.ready())
    {
        delay(1000);
    }
    
    Serial.println("GSM OK!!");
    
}


void loop()
{
     LSMS.beginSMS("9396553329");
     LSMS.print("LINKIT ONE WELCOMES YOU");
     LSMS.endSMS();
     delay(300);
     Serial.println("SMS SENT");
     LSMS.beginSMS("7799204041");
     LSMS.print("LINKIT ONE WELCOMES YOU");
     LSMS.endSMS();
     delay(300);
     Serial.println("SMS SENT");
     while(1);  
}

#include <LDateTime.h>

datetimeInfo t;
unsigned int rtc;

void setup() {
  Serial.begin(9600);
  datetimeInfo now;
  now.year = 2016;
  now.mon = 05;
  now.day = 07;
  now.hour=11;
  now.min=24;
  now.sec=10;
  LDateTime.setTime(&now);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  LDateTime.getTime(&t);
  LDateTime.getRtc(&rtc);
  delay(1000);
  Serial.print(t.day);
  Serial.print("/");
  Serial.print(t.mon);
  Serial.print("/");
  Serial.print(t.year);
  Serial.print(",");
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(":");
  Serial.println(t.sec);
}

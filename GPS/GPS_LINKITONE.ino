#include <LGPS.h>

gpsSentenceInfoStruct info;
char buff[256];

static unsigned char getComma(unsigned char num,const char *str)
{
  unsigned char i,j = 0;
  int len=strlen(str);
  for(i = 0;i < len;i ++)
  {
     if(str[i] == ',')
      j++;
     if(j == num)
      return i + 1; 
  }
  return 0; 
}

static double getDoubleNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;
  
  i=getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev=atof(buf);
  return rev; 
}

static double getIntNumber(const char *s)
{
  char buf[10];
  unsigned char i;
  double rev;
  
  i=getComma(1, s);
  i = i - 1;
  strncpy(buf, s, i);
  buf[i] = 0;
  rev=atoi(buf);
  return rev; 
}
void parseGPRMC(const char* GPRMCstr)
{
  double latitude;
  double longitude;
  int tmp;
  if(GPRMCstr[0] == '$')
  {
    tmp = getComma(1, GPRMCstr);
    tmp = getComma(3, GPRMCstr);
    latitude = getDoubleNumber(&GPRMCstr[tmp]);
    tmp = getComma(5, GPRMCstr);
    longitude = getDoubleNumber(&GPRMCstr[tmp]);
    sprintf(buff, "latitude = %10.4f, longitude = %10.4f", latitude, longitude);
    Serial.println(buff); 
    
    /*tmp = getComma(7, GPGGAstr);
    num = getIntNumber(&GPGGAstr[tmp]);    
    sprintf(buff, "satellites number = %d", num);
    Serial.println(buff);*/ 
  }
  else
  {
    Serial.println("Not get data"); 
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  LGPS.powerOn();
  Serial.println("LGPS Power on, and waiting ..."); 
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("LGPS loop"); 
  LGPS.getData(&info);
  //Serial.println((char*)info.GPRMC); 
  parseGPRMC((const char*)info.GPRMC);
  delay(2000);
}

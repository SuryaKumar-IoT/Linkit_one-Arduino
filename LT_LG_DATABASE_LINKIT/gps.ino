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
  int tmp;
  if(GPRMCstr[0] == '$')
  {
    tmp = getComma(1, GPRMCstr);
    tmp = getComma(3, GPRMCstr);
    latitude = getDoubleNumber(&GPRMCstr[tmp]);
    strcpy(lt,buf);
    
    tmp = getComma(5, GPRMCstr);
    longitude = getDoubleNumber(&GPRMCstr[tmp]);
    strcpy(lg,buf);  
  }
  else
  {
    Serial.println("Not get data"); 
  }
}

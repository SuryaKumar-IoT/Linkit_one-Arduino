void setup()
{
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  pinMode(3,HIGH);
}

void loop()
{
  if(digitalRead(2)==0)
  {
    digitalWrite(3,LOW);
  }
  else
    digitalWrite(3,HIGH);
}

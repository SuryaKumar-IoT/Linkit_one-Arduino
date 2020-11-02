void setup()
{
  Serial.begin(9600);
  Serial.println(" READ ANALOG PORT VALUE:");
}

void loop() 
{
  int n=analogRead(A0);
  int m=analogRead(A1);
  int p=analogRead(A2);
  
  Serial.print("SENSOR 1:");
  Serial.println(n);
  Serial.print("SENSOR 2:");
  Serial.println(m);
  Serial.print("SENSOR 3:");
  Serial.println(p);
  delay(1000); 
}

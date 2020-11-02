void setup()
{
 pinMode(3,OUTPUT);
 digitalWrite(3,HIGH);
  Serial1.begin(9600);
  
  Serial1.println("WELCOME TO LINKIT ONE");

}

void loop()
{
  Serial1.println(" SUCCESS SURYA");
  delay(300);
  digitalWrite(3,LOW);
  delay(300);
  digitalWrite(3,HIGH);
  delay(300);
  
}

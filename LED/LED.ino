const int pinLED = 3;                      // LED connect to D13
 
void setup()
{
    pinMode(pinLED, OUTPUT);                // set direction of D13-OUTPUT
}
 
void loop()
{
    digitalWrite(pinLED, LOW);             // LED on
    delay(300);
    digitalWrite(pinLED, HIGH);             // LED on
    delay(300);
    
}

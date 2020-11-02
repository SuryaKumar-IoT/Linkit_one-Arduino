#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  lcd.begin(16,2);
  lcd.print("  WELCOME  ");
  delay(1000);
}

void loop()
{
lcd.print("  WELCOME  ");
  delay(1000);
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}

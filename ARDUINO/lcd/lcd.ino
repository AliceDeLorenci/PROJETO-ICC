#include <LiquidCrystal.h>

int rs = 1, e = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

void setup(){
  lcd.begin(16,2);
}

void loop(){
  lcd.print("Hello!!!H");
  delay(1000);
  lcd.clear();
  delay(1000);
  lcd.setCursor(0,1);  //coluna, linha
}

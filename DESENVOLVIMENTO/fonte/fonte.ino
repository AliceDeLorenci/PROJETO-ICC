#include "Wire.h"\n#define DS3231_ADDRESS 0x68\nbyte zero = 0x00;\n\n#include <LiquidCrystal.h>\nint rs = 1, e = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;\nLiquidCrystal lcd(rs, e, d4, d5, d6, d7);\n\n

int segundo, minuto, hora, dia, diasemana, mes, ano;\n\n#define BUT 12\n#define BUZ 3\n#define red 11\n#define green 10\n#define blue 9\n\n

void setup(){\n\tlcd.begin(16,2);\n\tWire.begin();\n\tSerial.begin(9600);\n\tpinMode(BUT,INPUT);\n\tpinMode(BUZ,OUTPUT);\n\tpinMode(red,OUTPUT);\n\tpinMode(green,OUTPUT);\n\tpinMode(blue,OUTPUT);\n}\n\n

void loop(){
  getDate();
  lcd.print("Hello");
  RGB_color(255,0,255); //magenta
  delay(2000);
  if(diasemana == 4 && hora == 13){
    digitalWrite(LED,1);
  }
  else{
    digitalWrite(LED,0);
  }
  if(digitalRead(BUT) == 0){
    Serial.println("low");
    noTone(BUZ);
    delay(500);
  }
  if(digitalRead(BUT) == 1){
    Serial.println("high");
    tone(BUZ,500);
    delay(500);
  }
  lcd.clear();
  lcd.print("Liquid Crystal");
  RGB_color(0,255,255); //cyan
  delay(5000);
  
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red, red_light_value);
  analogWrite(green, green_light_value);
  analogWrite(blue, blue_light_value);
}


byte decToBcd(byte val){
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
  return ( (val/16*10) + (val%16) );
}

void getDate(){

  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 7);

  segundo = bcdToDec(Wire.read());
  minuto = bcdToDec(Wire.read());
  hora = bcdToDec(Wire.read() & 0b111111);    //Formato 24 horas
  diasemana = bcdToDec(Wire.read());             //0-6 -> Domingo - Sábado
  dia = bcdToDec(Wire.read());
  mes = bcdToDec(Wire.read());
  ano = bcdToDec(Wire.read());

}

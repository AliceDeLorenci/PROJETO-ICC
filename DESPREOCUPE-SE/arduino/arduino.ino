#include "Wire.h"
#define DS1307_ADDRESS 0x68
byte zero = 0x00;

#include <LiquidCrystal.h>
int rs = 12, e = 11, d4 = 8, d5 = 7, d6 = 4, d7 = 2;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

#define red 10
#define green 9
#define blue 6

#define BUT 5
#define BUZ 3

byte segundos, minutos, horas, diadasemana, diadomes, mes, ano;

byte ConverteParaBCD(byte val)
{
 return ( (val/10*16) + (val%10) );
}

 byte ConverteparaDecimal(byte val) 
{ 
 return ( (val/16*10) + (val%16) );
}

void Relogio()
{
 Wire.beginTransmission(DS1307_ADDRESS);
 Wire.write(zero);
 Wire.endTransmission();
 Wire.requestFrom(DS1307_ADDRESS, 7);
 segundos = ConverteparaDecimal(Wire.read());
 minutos = ConverteparaDecimal(Wire.read());
 horas = ConverteparaDecimal(Wire.read() & 0b111111);
 diadasemana = ConverteparaDecimal(Wire.read());
 diadomes = ConverteparaDecimal(Wire.read());
 mes = ConverteparaDecimal(Wire.read());
 ano = ConverteparaDecimal(Wire.read());
}

void color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(red, red_light_value);
  analogWrite(green, green_light_value);
  analogWrite(blue, blue_light_value);
}

void setup()
{
 lcd.begin(16, 2);
 Wire.begin();
 Serial.begin(9600);

 pinMode(red,OUTPUT);
 pinMode(green,OUTPUT);
 pinMode(blue,OUTPUT);
 pinMode(BUT,INPUT);
 pinMode(BUZ,OUTPUT);
}

void loop()
{
 Relogio();
 if(minutos%10 == 0){
  if(diadasemana == 5){
   if((horas == 15 && 30 >= minutos && 30 < minutos+10)){
    int i;
    for(i=0 ; i<10 ; i++){
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     lcd.setCursor(0,0);
     lcd.print("REMEDIO PARA DOR");
     lcd.setCursor(0,1);
     lcd.print("2 COMPRIMIDOS");
     color(0,255,0);
     analogWrite(BUZ,9640);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,409);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,8000);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,304);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,0);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(2000);
     lcd.clear();
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(1000);
    }
    color(0,0,0);

   }
  }
  
  if(diadasemana == 0){
   if((horas == 15 && 30 >= minutos && 30 < minutos+10) || (horas == 16 && 0 >= minutos && 0 < minutos+10) || (horas == 18 && 0 >= minutos && 0 < minutos+10)){
    int i;
    for(i=0 ; i<10 ; i++){
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     lcd.setCursor(0,0);
     lcd.print("ANTIALERGICO");
     lcd.setCursor(0,1);
     lcd.print("4 COMPRIMIDOS");
     color(255,0,255);
     analogWrite(BUZ,304);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,10340);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,430);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,7700);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,0);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(2000);
     lcd.clear();
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(1000);
    }
    color(0,0,0);

   }
  }
  
  if(diadasemana == 2 || diadasemana == 3){
   if((horas == 16 && 0 >= minutos && 0 < minutos+10) || (horas == 19 && 0 >= minutos && 0 < minutos+10) || (horas == 21 && 0 >= minutos && 0 < minutos+10)){
    int i;
    for(i=0 ; i<10 ; i++){
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     lcd.setCursor(0,0);
     lcd.print("REMEDIO DE PRESSAO");
     lcd.setCursor(0,1);
     lcd.print("3 COMPRIMIDOS");
     color(0,255,255);
     analogWrite(BUZ,8200);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,295);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,10250);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,357);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(500);
     analogWrite(BUZ,0);
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(2000);
     lcd.clear();
     if(digitalRead(BUT)==1){
      color(0,0,0);
      analogWrite(BUZ,0);
      lcd.clear();
      delay(10000);
      break;
     }
     delay(1000);
    }
    color(0,0,0);

   }
  }
  
 delay(60000);
 }
}


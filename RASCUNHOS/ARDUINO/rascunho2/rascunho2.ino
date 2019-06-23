/******************* RTC *********************/
#include "Wire.h"
#define DS3231_ADDRESS 0x68
byte zero = 0x00;
/********************************************/

/******************* LCD ********************/
#include <LiquidCrystal.h>

int rs = 1, e = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;

LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
/********************************************/

int segundo, minuto, hora, dia, diasemana, mes, ano;

#define LED 13
#define BUT 12
#define BUZ 3

/******************* RGB ********************/
#define red 11
#define green 10
#define blue 9
/********************************************/

void setup(){
  lcd.begin(16,2);
  Wire.begin();
  Serial.begin(9600);
  //setDateTime();    //CONFIGURAR SE NECESSARIO
  pinMode(LED,OUTPUT);
  pinMode(BUT,INPUT);
  pinMode(BUZ,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
}

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

void setDateTime(){

  byte segundo = 30;  //0-59
  byte minuto = 37;  //0-59
  byte hora = 10;  //0-23
  byte diasemana = 6;  //1-7
  byte dia = 24;  //1-31
  byte mes = 5; //1-12
  byte ano  = 19; //0-99

  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(zero); 

  Wire.write(decToBcd(segundo));
  Wire.write(decToBcd(minuto));
  Wire.write(decToBcd(hora));
  Wire.write(decToBcd(diasemana));
  Wire.write(decToBcd(dia));
  Wire.write(decToBcd(mes));
  Wire.write(decToBcd(ano));

  Wire.write(zero); 

  Wire.endTransmission();

}

byte decToBcd(byte val){
// Conversão de decimal para binário
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
// Conversão de binário para decimal
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

/*
//Exibe a data e hora. Ex.:   3/12/13 19:00:00
  
  Serial.print(dia);
  Serial.print("/");
  Serial.print(mes);
  Serial.print("/");
  Serial.print(ano);
  Serial.print(" ");
  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.println(segundo);
 */

}

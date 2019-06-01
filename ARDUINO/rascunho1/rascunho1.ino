
// RealTimeClock DS3231

#include <Wire.h>    // or "Wire.h>
#define DS3231_ADDRESS 0x68
byte zero = 0x00;


/*
  Real Time Clock
 * RTC GND to GND
 * RTC VCC tp 5V
 * RTC SDA to analog pin A4
 * RTC SCL to analog pin A5
*/



/*
  LiquidCrystal Display

 16x2 LCD display

  The circuit:
 * LCD RS pin to digital pin 1
 * LCD Enable pin to digital pin 2
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/

#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 1, en = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define LED 13
#define BUZZ 9
#define BUT 8

void setup(){
  
  Wire.begin();
  //setDateTime();            //once setDateTime is configured and compiled, this line can be commented, as the RTC will keep
                            //track of the time by itself

  
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  
  pinMode(BUZZ,OUTPUT);
  pinMode(LED,OUTPUT);
  pinMode(BUT,INPUT);
  
}

void loop(){
 

  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 7);

  int segundo = bcdToDec(Wire.read());
  int minuto = bcdToDec(Wire.read());
  int hora = bcdToDec(Wire.read() & 0b111111);    //Formato 24 horas
  int diasemana = bcdToDec(Wire.read());          //0-6 -> Domingo - Sábado
  int dia = bcdToDec(Wire.read());
  int mes = bcdToDec(Wire.read());
  int ano = bcdToDec(Wire.read());

  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.print(segundo);
  Serial.print(" ");
  Serial.print(diasemana);
  Serial.print(" ");
  Serial.print(dia);
  Serial.print("/");
  Serial.print(mes);
  Serial.print("/");
  Serial.println(ano);
  delay(1000);

  if(diasemana == 3 && hora == 13){
    digitalWrite(LED,HIGH);
  }

}

void setDateTime(){

  byte segundo = 10;  //0-59
  byte minuto = 12;  //0-59
  byte hora = 14;  //0-23
  byte diasemana = 3;  //1-7
  byte dia = 28;  //1-31
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

void printDate(){

  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 7);

  int segundo = bcdToDec(Wire.read());
  int minuto = bcdToDec(Wire.read());
  int hora = bcdToDec(Wire.read() & 0b111111);    //Formato 24 horas
  int diasemana = bcdToDec(Wire.read());          //0-6 -> Domingo - Sábado
  int dia = bcdToDec(Wire.read());
  int mes = bcdToDec(Wire.read());
  int ano = bcdToDec(Wire.read());

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

}

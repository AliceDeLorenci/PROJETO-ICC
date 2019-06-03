//https://www.robocore.net/tutoriais/modulo-rtc-arduino.html
//https://www.youtube.com/watch?v=E6wkvTG2Ofs

#include "Wire.h"
#define DS3231_ADDRESS 0x68
byte zero = 0x00;


void setup(){
  Wire.begin();
  Serial.begin(9600);
  setDateTime();            //Necessário configurar na função "setDateTime()"   //uma vez configurada e compilada, deve ser comentada
                                                                                //o RTC continuara a contagem do tempo independentemente
}

void loop(){
  printDate();
  delay(1000);
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

void printDate(){

  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(zero);
  Wire.endTransmission();

  Wire.requestFrom(DS3231_ADDRESS, 7);

  int segundo = bcdToDec(Wire.read());
  int minuto = bcdToDec(Wire.read());
  int hora = bcdToDec(Wire.read() & 0b111111);    //Formato 24 horas
  int diasemana = bcdToDec(Wire.read());             //0-6 -> Domingo - Sábado
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

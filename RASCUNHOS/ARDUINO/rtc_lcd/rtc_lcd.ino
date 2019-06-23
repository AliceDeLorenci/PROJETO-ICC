// Programa: Relogio com modulo DS3231 e LCD 16x2

 
#include "Wire.h"
#include <LiquidCrystal.h>
 
#define DS1307_ADDRESS 0x68
 
// Inicializa o LCD
LiquidCrystal lcd(12, 11, 8, 7, 4, 2);
 
byte zero = 0x00; 
 
void setup()
{
 // Define o LCD com 16 colunas e 2 linhas
 lcd.begin(16, 2);
 Wire.begin();
 Serial.begin(9600);
 // A linha abaixo pode ser retirada apos setar a data e hora
 // SelecionaDataeHora(); 
}
 
void loop()
{
 Mostrarelogio();
 delay(1000);
}
 
void SelecionaDataeHora() // Seta a data e a hora do DS1307
{
 byte segundos = 01; // Valores de 0 a 59
 byte minutos = 59; // Valores de 0 a 59
 byte horas = 23; // Valores de 0 a 23
 byte diadasemana = 4; // Valores de 0 a 6 (0=Domingo, 1 = Segunda...)
 byte diadomes = 23; // Valores de 1 a 31
 byte mes = 4; // Valores de 1 a 12
 byte ano = 15; // Valores de 0 a 99
 Wire.beginTransmission(DS1307_ADDRESS);
 // Stop no CI para que o mesmo possa receber os dados
 Wire.write(zero); 
 
 // As linhas abaixo escrevem no CI os valores de 
 // data e hora que foram colocados nas variaveis acima
 Wire.write(ConverteParaBCD(segundos));
 Wire.write(ConverteParaBCD(minutos));
 Wire.write(ConverteParaBCD(horas));
 Wire.write(ConverteParaBCD(diadasemana));
 Wire.write(ConverteParaBCD(diadomes));
 Wire.write(ConverteParaBCD(mes));
 Wire.write(ConverteParaBCD(ano));
 Wire.write(zero); //Start no CI
 Wire.endTransmission(); 
}
 
byte ConverteParaBCD(byte val)
{ 
 // Converte o número de decimal para BCD
 return ( (val/10*16) + (val%10) );
}
 
byte ConverteparaDecimal(byte val) 
{ 
 // Converte de BCD para decimal
 return ( (val/16*10) + (val%16) );
}
 
void Mostrarelogio()
{
 Wire.beginTransmission(DS1307_ADDRESS);
 Wire.write(zero);
 Wire.endTransmission();
 Wire.requestFrom(DS1307_ADDRESS, 7);
 int segundos = ConverteparaDecimal(Wire.read());
 int minutos = ConverteparaDecimal(Wire.read());
 int horas = ConverteparaDecimal(Wire.read() & 0b111111); 
 int diadasemana = ConverteparaDecimal(Wire.read()); 
 int diadomes = ConverteparaDecimal(Wire.read());
 int mes = ConverteparaDecimal(Wire.read());
 int ano = ConverteparaDecimal(Wire.read());
 
 // Mostra a hora atual no display
 lcd.setCursor(0, 0);
 if (horas < 10){
  lcd.print("0");
 }
 lcd.print(horas);
 lcd.print(":");
 if (minutos < 10){
  lcd.print("0");
 }
 lcd.print(minutos);
 lcd.print(":");
 if (segundos < 10){
  lcd.print("0");
 }
 lcd.print(segundos);
  
 // Mostra a data atual no display
 lcd.setCursor(0, 1);
 //lcd.print("Data : ");
 if (diadomes < 10){
  lcd.print("0");
 }
 lcd.print(diadomes);
 lcd.print(".");
 if (mes < 10){
  lcd.print("0");
 }
 lcd.print(mes);
 lcd.print(".");
 lcd.print(ano);
  
 //Mostra o dia da semana no display
 lcd.print(" ");
 switch(diadasemana)
 {
 case 0:lcd.print("DOM");
 break;
 case 1:lcd.print("SEG");
 break;
 case 2:lcd.print("TER");
 break;
 case 3:lcd.print("QUA");
 break;
 case 4:lcd.print("QUI");
 break;
 case 5:lcd.print("SEX");
 break;
 case 6:lcd.print("SAB");
 }
}

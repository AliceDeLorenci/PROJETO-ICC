#include "Wire.h"
#define DS3231_ADDRESS 0x68
byte zero = 0x00;

#include <LiquidCrystal.h>
int rs = 1, e = 2, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7

int segundo, minuto, hora, dia, diasemana, mes, ano;

#define BUT 12
#define BUZ 3
#define red 11
#define green 10
#define blue 9

void setup(){
	lcd.begin(16,2);
	Wire.begin();
	Serial.begin(9600);
	pinMode(BUT,INPUT);
	pinMode(BUZ,OUTPUT);
	pinMode(red,OUTPUT);
	pinMode(green,OUTPUT);
	pinMode(blue,OUTPUT);
}


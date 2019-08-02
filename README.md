# ALARME PARA MEDICAMENTOS

## SISTEMA OPERACIONAL

**Linux** (Ubunto 18.04)


## INSTALAÇÕES NECESSÁRIAS

### GCC

		~$ sudo apt-get install gcc


### ARDUINO IDE

https://www.arduino.cc/en/Guide/Linux

### ARDUINO-MK

O programa desenvolvido compila e faz o upload do arquivo .ino gerado automaticamente, sem que o usuário tenha que utilizar a ARDUINO IDE, para isso é necessário instalar o **arduino-mk** 


		~$ sudo apt-get install arduino-mk

Que será instalado em:

		~$ cd //usr/share/arduino

O funcionamento dessa aplicação depende do arquivo **Makefile** já contido na pasta **DESPREOCUPE-SE/Arduino**


### GTK LIBRARY

		~$ sudo apt-get install libgtk2.0-dev

		~$ sudo apt install libcanberra-gtk-module libcanberra-gtk3-module


## COMPILAR ARQUIVO C++:

Para que o arquivo seja compilado a pasta **DESPREOCUPE-SE** deve ser salva em **Desktop** caso contrário a função **system()** não funcionará, e o path terá que ser modificado.

Diretivas para compilar o programa a apartir do terminal:

		~$ cd Desktop/DESPREOCUPE-SE
		
		~/Desktop/DESPREOCUPE-SE$ g++ -Wall backend.cpp -o prog

		~/Desktop/DESPREOCUPE-SE$ ./prog
		
		
		
		~$ cd Desktop/DESPREOCUPE-SE

		~/Desktop/DESPREOCUPE-SE$ g++ interface.cpp -o prog `pkg-config --libs --cflags  gtk+-3.0`

		~/Desktop/DESPREOCUPE-SE$ ./prog




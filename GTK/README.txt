INSTALLING GTK

$ sudo apt-get install libgtk2.0-dev

$ sudo apt install libcanberra-gtk-module libcanberra-gtk3-module

LIBRARY

#include <gtk/gtk.h>

COMPILING

$ g++ first.cpp -o prog `pkg-config --libs gtk+-2.0` `pkg-config --cflags gtk+-2.0`

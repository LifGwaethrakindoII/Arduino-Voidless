#ifndef VSTRING_H
#define VSTRING_H

#include <Arduino.h>

String boolToString(bool b);
String intToBits(int x);
String byteToBits(byte b);
String buttonState(String name, int buttonData, byte bit);
void debugAsPersistentText(String text);

#endif
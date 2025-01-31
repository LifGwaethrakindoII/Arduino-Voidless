#include <Arduino.h>
#include <VString.h>
#include <SNESController.h>

SNESController snesController;

void setup()
{
  Serial.begin(9600); // Start serial communication for debugging
  snesController = SNESController();
}

void loop()
{
  snesController.update();
  debugAsPersistentText(snesController.toString());
  delay(100);
}
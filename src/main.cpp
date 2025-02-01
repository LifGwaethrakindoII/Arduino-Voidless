#include <Arduino.h>
#include <VString.h>
#include <SNESController.h>
#include <VDebug.h>
#include <GameBoyAdvance.h>

SNESController snesController;
GameBoyAdvance gameBoyAdvance;

void setup()
{
  Serial.begin(9600); // Start serial communication for debugging
  snesController = SNESController();
  gameBoyAdvance = GameBoyAdvance();
}

void loop()
{
  snesController.update();
  debugAsPersistentText(snesController.toString());
  delay(100);
}
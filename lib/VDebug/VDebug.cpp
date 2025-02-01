#include <Arduino.h>
#include <VDebug.h>

void debugAsPersistentText(String text)
{
    // Send the ANSI escape code to clear the screen
    // Serial.print("\033c");  // Or Serial.print("\x1Bc");
    Serial.print("\033[H"); // Clear screen and move cursor to the top-left
    Serial.println(text);
}
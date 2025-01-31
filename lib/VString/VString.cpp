#include <VString.h>
#include <Arduino.h>

String boolToString(bool b)
{
    return b ? "True" : "False";
}

String intToBits(int x)
{
    String bits = "";

    for (int i = 0; i < 16; i++)
    {
        bits += (x | 1 << i) == x ? "1" : "0";
    }

    return bits;
}

String byteToBits(byte b)
{
    String bits = "";

    for (int i = 0; i < 8; i++)
    {
        bits += (b | 1 << i) == b ? "1" : "0";
    }

    return bits;
}

String buttonState(String name, int buttonData, byte bit)
{
    return name + ": " + ((buttonData & (1 << bit)) ? "Pressed" : "Released");
}

void debugAsPersistentText(String text)
{
    // Send the ANSI escape code to clear the screen
    // Serial.print("\033c");  // Or Serial.print("\x1Bc");
    Serial.print("\033[H"); // Clear screen and move cursor to the top-left
    Serial.println(text);
}
#include <VString.h>
#include <Arduino.h>

String boolToString(bool b)
{
    return b ? "True" : "False";
}

String intToBits(int x)
{
    String bits = "";

    for (int i = 0; i < 32; i++)
    {
        bits += (x | 1 << i) == x ? "1" : "0";
    }

    return bits;
}

String int16ToBits(uint16_t x)
{
    String bits = "";

    for (int i = 0; i < 16; i++)
    {
        bits += (x & (1 << i)) ? "1" : "0";
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
#include "SNESController.h"
#include <Arduino.h>
#include <VString.h>

#define BIT_B 0
#define BIT_Y 1
#define BIT_SELECT 2
#define BIT_START 3
#define BIT_UP 4
#define BIT_DOWN 5
#define BIT_LEFT 6
#define BIT_RIGHT 7
#define BIT_A 8
#define BIT_X 9
#define BIT_L 10
#define BIT_R 11

/*
SNES Controller Pins:

1: 5V (Power)
2: Clock
3: Latch
4: Data
5: -
6: GND (Ground)
7: -
*/

enum SNESButtons
{
    B = 0,
    Y = 1,
    SELECT = 2,
    START = 4,
    UP = 8,
    DOWN = 16,
    LEFT = 32,
    RIGHT = 64,
    A = 128,
    X = 256,
    L = 512,
    R = 1024
};

SNESController::SNESController()
{
    clockPin = PIN_CLOCK;
    latchPin = PIN_LATCH;
    dataPin = PIN_DATA;
    pressedButtons = 0;
    previousPressedButtons = 0;
    connected = false;
    previousConnected = false;
    setupPins();
}

SNESController::SNESController(int _clockPin, int _latchPin, int _dataPin)
{
    clockPin = _clockPin;
    latchPin = _latchPin;
    dataPin = _dataPin;
    pressedButtons = 0;
    previousPressedButtons = 0;
    connected = false;
    previousConnected = false;
    setupPins();
}

void SNESController::update()
{
    // Check the data pin before reading
    bool dataPinStateBefore = digitalRead(dataPin);

    // Read the controller
    latchPulse();
    readController();

    // Check the data pin after reading
    bool dataPinStateAfter = digitalRead(dataPin);

    // If the data pin remained HIGH throughout, assume no controller is connected
    connected = !(dataPinStateBefore == HIGH && dataPinStateAfter == HIGH);

    previousConnected = connected;
    previousPressedButtons = pressedButtons;
}

/*bool SNESController::buttonPressed(SNESButtons button)
{
    return connected ? (pressedButtons | (1 << button)) == pressedButtons : false;
}*/ 

void SNESController::setupPins()
{
    pinMode(clockPin, OUTPUT);
    digitalWrite(clockPin, HIGH); // Default clock HIGH

    pinMode(latchPin, OUTPUT);
    digitalWrite(latchPin, LOW); // Default latch LOW

    pinMode(dataPin, INPUT_PULLUP); // Use pull-up resistor for stable readings
}

void SNESController::latchPulse()
{
    digitalWrite(latchPin, HIGH);
    delayMicroseconds(12); // Hold the latch signal for 12µs
    digitalWrite(latchPin, LOW);
    delayMicroseconds(6); // Allow a short settling period
}

void SNESController::readController()
{
    pressedButtons = 0;

    for (int i = 0; i < 16; i++)
    {
        // Read the current button state from the data line
        int buttonState = digitalRead(dataPin);

        // If the button is pressed, set the corresponding bit
        // LOW means pressed for SNES controllers
        if(buttonState == LOW) pressedButtons |= (1 << i);

        // Pulse the clock to shift to the next button
        digitalWrite(clockPin, LOW);
        delayMicroseconds(6); // Short delay for stability
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(6); // Short delay for stability
    }
}

String SNESController::toString()
{
    String builder = "Pins: { Clock = ";
    builder += clockPin;
    builder += ", Latch = ";
    builder += latchPin;
    builder += ", Data = ";
    builder += dataPin;
    builder += " }";
    builder += "\r\n";
    builder += "Button States (as Bitchain): ";
    builder += int16ToBits(pressedButtons);
    builder += "\r\n";
    builder += "Connected: ";
    builder += boolToString(connected);
    builder += "\r\n";
    builder += buttonStatesToString();

    return builder;
}

String SNESController::buttonStatesToString()
{
    String s = "--------------------\r\n";
    s += "Button States: \r\n";

    s += (buttonState("B", pressedButtons, BIT_B));
    s += "\r\n";
    s += (buttonState("Y", pressedButtons, BIT_Y));
    s += "\r\n";
    s += (buttonState("Select", pressedButtons, BIT_SELECT));
    s += "\r\n";
    s += (buttonState("Start", pressedButtons, BIT_START));
    s += "\r\n";
    s += (buttonState("Up", pressedButtons, BIT_UP));
    s += "\r\n";
    s += (buttonState("Down", pressedButtons, BIT_DOWN));
    s += "\r\n";
    s += (buttonState("Left", pressedButtons, BIT_LEFT));
    s += "\r\n";
    s += (buttonState("Right", pressedButtons, BIT_RIGHT));
    s += "\r\n";
    s += (buttonState("A", pressedButtons, BIT_A));
    s += "\r\n";
    s += (buttonState("X", pressedButtons, BIT_X));
    s += "\r\n";
    s += (buttonState("L", pressedButtons, BIT_L));
    s += "\r\n";
    s += (buttonState("R", pressedButtons, BIT_R));
    s += "\r\n";

    s += "--------------------";

    return s;
}
#ifndef SNESCONTROLLER_H
#define SNESCONTROLLER_H

#include <Arduino.h>
#include <VString.h>

// Default pins if user does not define them during construction:
#define PIN_CLOCK 2
#define PIN_LATCH 3
#define PIN_DATA 4

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

class SNESController
{
public:
    SNESController();
    SNESController(int _clockPin, int _latchPin, int _dataPin);

    uint16_t getPressedButtons() { return pressedButtons; }
    uint16_t getPreviousPressedButtons() { return previousPressedButtons; }
    bool getConnected() { return connected; }
    bool getPreviousConnected() { return previousConnected; }

    void update();
    //bool buttonPressed(SNESButtons button);
    String buttonStatesToString();
    String toString();

private:
    int clockPin;
    int latchPin;
    int dataPin;
    uint16_t pressedButtons;
    uint16_t previousPressedButtons;
    bool connected;
    bool previousConnected;

    void evaluateConnected();
    void setupPins();
    void latchPulse();
    void readController();
};

#endif
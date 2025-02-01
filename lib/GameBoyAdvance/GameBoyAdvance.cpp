#include "GameBoyAdvance.h"
#include <Arduino.h>
#include <VString.h>

GameBoyAdvance::GameBoyAdvance()
{
    clockPin = PIN_CLOCK;
    latchPin = PIN_LATCH;
    dataPin = PIN_DATA;
}

GameBoyAdvance::GameBoyAdvance(int _clockPin, int _latchPin, int _dataPin)
{
    clockPin = _clockPin;
    latchPin = _latchPin;
    dataPin = _dataPin;
    connected = false;
}

uint16_t GameBoyAdvance::mapSNESToGBA(uint16_t pressedButtons)
{
    uint16_t buttons = 0;

    // Map SNES buttons to GBA buttons
    if(pressedButtons & (1 << 0)) buttons |= (1 << 0); // B -> A
    if(pressedButtons & (1 << 1)) buttons |= (1 << 1); // Y -> B
    if(pressedButtons & (1 << 2)) buttons |= (1 << 2); // Select -> Select
    if(pressedButtons & (1 << 3)) buttons |= (1 << 3); // Start -> Start
    if(pressedButtons & (1 << 4)) buttons |= (1 << 4); // Up -> Up
    if(pressedButtons & (1 << 5)) buttons |= (1 << 5); // Down -> Down
    if(pressedButtons & (1 << 6)) buttons |= (1 << 6); // Left -> Left
    if(pressedButtons & (1 << 7)) buttons |= (1 << 7); // Right -> Right
    if(pressedButtons & (1 << 10)) buttons |= (1 << 8); // L -> L
    if(pressedButtons & (1 << 11)) buttons |= (1 << 9); // R -> R

    return buttons;
}

void GameBoyAdvance::sendInput(uint16_t buttons)
{
    // Send latch pulse
    digitalWrite(latchPin, HIGH);
    delayMicroseconds(4);
    digitalWrite(latchPin, LOW);

    // Shift out button states
    for (int i = 0; i < 16; i++)
    {
        digitalWrite(clockPin, LOW);
        digitalWrite(dataPin, (buttons & (1 << i)) ? HIGH : LOW);
        delayMicroseconds(4);
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(4);
    }
}
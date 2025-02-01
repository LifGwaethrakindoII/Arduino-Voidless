#include <Arduino.h>
#include <VString.h>
#include <SNESController.h>

// Default pins if user does not define them during construction:
#define PIN_CLOCK 5
#define PIN_LATCH 6
#define PIN_DATA 7

enum GBAButtons
{
    A = 0,
    B = 1,
    SELECT = 2,
    START = 4,
    RIGHT = 8,
    LEFT = 16,
    UP = 32,
    DOWN = 64,
    L = 128,
    R = 256
};

class GameBoyAdvance
{
    private:
        int clockPin;
        int latchPin;
        int dataPin;
        bool connected;

    public:
        GameBoyAdvance();
        GameBoyAdvance(int _clockPin, int _latchPin, int _dataPin);
        uint16_t mapSNESToGBA(uint16_t pressedButtons);
        void sendInput(uint16_t buttons);
};
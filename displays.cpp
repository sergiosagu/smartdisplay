#include <iostream>
#include <string>
#include "displays.hpp"

#ifdef WPI
#include <wiringPi.h>
#else

#define OUTPUT 1

#define LOW 0
#define HIGH 1

int piHiPri(const int pri)
{
    printf("piHiPri - pri '%i'\n", pri);
    return 0;
}

int wiringPiSetupGpio(void)
{
    printf("wiringPiSetupGpio\n");
    return 0;
}

void pinMode(int pin, int mode)
{
    printf("pinMode - pin '%i', mode '%i'\n", pin, mode);
}

void digitalWrite(int pin, int value)
{
    printf("digitalWrite - pin '%i', value '%i'\n", pin, value);
}

void delay(unsigned int howLong)
{
    printf("delay - howLong '%i'\n", howLong);
}

void delayMicroseconds(unsigned int howLong)
{
    printf("delayMicroseconds - howLong '%i'\n", howLong);
}

#endif

using namespace std;

Display::Display(byte sclk, byte data, byte rset)
{
    this->sclk = sclk;
    this->data = data;
    this->rset = rset;
}

Display::~Display()
{
}

void Display::demo()
{
    string msg = " the cpp demo s ";

    pause(1);

    fadeIn(msg);
    print(msg, 2000, BRIGHTNESS_MAX);
    fadeOut(msg);
    pause(1);
}

void Display::print(string msg, int msgDelay, byte brightness)
{
    // printf("smart print '%s', '%i', '%i'\n", msg, msgDelay, brightness);
    cout << "smart print '" << msg << "'\n";
    setBrightness(brightness);
    for (int i = 0; i < DISPLAY_SIZE; i++)
    {
        writeChar(msg[i]);
    }
    delay(msgDelay);
}

void Display::fadeIn(string msg)
{
    for (int i = 0; i <= BRIGHTNESS_MAX; i++)
    {
        print(msg, FADE_DELAY, i);
    }
}

void Display::fadeOut(string msg)
{
    for (int i = BRIGHTNESS_MAX; i >= 0; i--)
    {
        print(msg, FADE_DELAY, i);
    }
}

void Display::pause(byte seconds)
{
    print(BLANK_DISPLAY, seconds * 1000, BRIGHTNESS_MIN);
}

void Display::setBrightness(byte brightness)
{
    // printf("smart setBrightness '%i'\n", brightness);

    if (this->currentBrightness != brightness)
    {
        writeByte(BRIGHTNESS_MASK | brightness);
        this->currentBrightness = brightness;
    }
}

void Display::writeChar(char aChar)
{
    // printf("smart writeChar '%c'\n", aChar);

    writeByte(getChar(aChar));
}

char Display::getChar(char c)
{
    // printf("smart getChar '%c'\n", c);

    // ASCII from space to '?'
    if ((c >= 32) && (c <= 63))
    {
        return c;
    }
    // ASCII from '@' to '_'
    if ((c >= 64) && (c <= 95))
    {
        return c - 64;
    }
    // ASCII from '@' to '_'
    if ((c >= 96) && (c <= 127))
    {
        return c - 96;
    }
    return 63; // '?'
}

void Display::writeByte(byte aByte)
{
    // printf("writeByte '%i' sclk '%i' data '%i' rset '%i'\n", aByte, this->sclk, this->data, this->rset);
    for (int i = 0; i < 8; i++)
    {
        bool bit = (((aByte >> (7 - i)) & 0x01) == 1);
        writeBit(bit);
        // writeBit(bitRead(aByte, 7 - i));
    }
}

void Display::writeBit(bool aBit)
{
    digitalWrite(this->data, aBit ? HIGH : LOW);
    delayMicroseconds(BIT_DELAY);

    digitalWrite(this->sclk, HIGH);
    delayMicroseconds(HIGH_DELAY);

    digitalWrite(this->sclk, LOW);
    delayMicroseconds(LOW_DELAY);
}

void Display::reset()
{
    // printf("-----reset sclk '%i' data '%i' rset '%i'\n", this->sclk, this->data, this->rset);

    digitalWrite(this->data, LOW);
    digitalWrite(this->sclk, LOW);
    digitalWrite(this->rset, LOW);
    delay(RESET_DELAY);
    digitalWrite(this->rset, HIGH);
    delay(RESET_DELAY);
}

void Display::init()
{
    // printf("superreset sclk '%i' data '%i' rset '%i'\n", this->sclk, this->data, this->rset);
    pinMode(this->sclk, OUTPUT);
    pinMode(this->data, OUTPUT);
    pinMode(this->rset, OUTPUT);

    reset();

    writeByte(COUNTER_CONTROL);
    writeByte(POINTER_CONTROL);
    setBrightness(BRIGHTNESS_MAX);
}

void Display::libSetup()
{
    piHiPri(99);
    wiringPiSetupGpio();
}
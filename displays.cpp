#include <iostream>
#include <string>
#include <cstdlib>
#include "displays.hpp"

#ifdef WPI
#include <wiringPi.h>
#else

#include <chrono>
#include <thread>

#define OUTPUT 1

#define LOW 0
#define HIGH 1

int piHiPri(const int pri)
{
    return 0;
}

int wiringPiSetupGpio(void)
{
    return 0;
}

void pinMode(int pin, int mode)
{
}

void digitalWrite(int pin, int value)
{
}

void delay(unsigned int howLong)
{
    this_thread::sleep_for(chrono::milliseconds(howLong));
}

void delayMicroseconds(unsigned int howLong)
{
    this_thread::sleep_for(chrono::microseconds(howLong));
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
    string txt = "quick demo";
    string msg = alignCenter(txt);

    pause(1);

    fadeIn(msg);
    print(msg, 2000, BRIGHTNESS_MAX);
    fadeOut(msg);
    pause(1);

    slideLeft(txt);
    slideRight(txt);
    pause(1);

    string msgl = alignLeft(txt);
    for (int i = 0; i < 5; i++)
        fadeBlink(msgl);
    pause(1);

    string msgr = alignRight(txt);
    for (int i = 0; i < 5; i++)
        blink(msgr);
    pause(1);

    crack(msg);
    print(msg, 2000, BRIGHTNESS_MAX);
    pause(1);

    term(txt);
    pause(1);
}

void Display::print(string msg, int msgDelay, byte brightness)
{
    cout << "[" << msg << "] (" << msgDelay << "ms) (" << (unsigned int)brightness << ")\n";
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

void Display::fadeBlink(string msg)
{
    fadeIn(msg);
    fadeOut(msg);
}

void Display::blink(string msg)
{
    print(msg, BLINK_DELAY, BRIGHTNESS_MIN);
    print(msg, BLINK_DELAY, BRIGHTNESS_MAX);
}

void Display::slideLeft(string msg)
{
    msg = BLANK_DISPLAY + msg;
    int size = msg.length();
    for (int i = 0; i < size; i++)
    {
        string txt = "";
        for (int j = 0; j < DISPLAY_SIZE; j++)
        {
            txt = txt + msg[(i + j) % size];
        }
        print(txt, SLIDE_DELAY, BRIGHTNESS_MAX);
    }
}

void Display::slideRight(string msg)
{
    msg = msg + BLANK_DISPLAY;
    int size = msg.length();
    for (int i = size - 1; i >= 0; i--)
    {
        string txt = "";
        for (int j = 0; j < DISPLAY_SIZE; j++)
        {
            txt = msg[((i - j) + size) % size] + txt;
        }
        print(txt, SLIDE_DELAY, BRIGHTNESS_MAX);
    }
}

char randomChar()
{
    char c = (rand() % 36) + 65; // A to Z + 10 digits
    if (c > 90)
    {
        c = (c - 91) + 48; // digits 0 to 9
    }
    return c;
}

string randomText(byte size)
{
    string txt = "";
    for (int i = 0; i < size; i++)
    {
        txt += randomChar();
    }
    return txt;
}

string blankText(byte size)
{
    string txt = "";
    txt.resize(size, ' ');
    return txt;
}

void Display::crack(string msg)
{
    bool mask[DISPLAY_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    // initial cracking noise
    for (int n = 0; n < CRACK_NOISE; n++)
    {
        print(randomText(DISPLAY_SIZE), CRACK_DELAY, BRIGHTNESS_MAX);
    }

    for (int i = 0; i < DISPLAY_SIZE; i++)
    {
        // pick the next char to crack
        bool set = false;
        while (!set)
        {
            byte pos = rand() % DISPLAY_SIZE;
            if (mask[pos] == 0)
            {
                mask[pos] = 1;
                set = true;
            }
        }
        // cracking process with already cracked chars
        for (int n = 0; n < CRACK_NOISE; n++)
        {
            string txt = "";
            for (int j = 0; j < DISPLAY_SIZE; j++)
            {
                if (mask[j] == 0)
                {
                    txt += randomChar();
                }
                else
                {
                    txt += msg[j];
                }
            }
            print(txt, CRACK_DELAY, BRIGHTNESS_MAX);
        }
    }
}

void Display::term(string msg)
{
    // initial blinks
    for (int i = 0; i < TERM_BLINK; i++)
        blink(alignLeft("_"));

    int size = msg.length() + 1;
    if (size > DISPLAY_SIZE)
    {
        size++; // one more loop cycle for the final cursor
    }

    string txt;
    byte cursorAt = 0;

    for (int i = 0; i < size; i++)
    {
        txt = "";
        for (int j = 0; j < min(DISPLAY_SIZE - 1, i); j++)
        {
            if (i < DISPLAY_SIZE)
            {
                txt += msg[j];
            }
            else
            {
                txt += msg[j + i - DISPLAY_SIZE];
            }
        }
        txt += "_";
        cursorAt = txt.length() - 1;
        txt += blankText(max(0, DISPLAY_SIZE - (i + 1)));
        print(txt, TERM_DELAY, BRIGHTNESS_MAX);
    }

    // final blinks
    for (int i = 0; i < (TERM_BLINK * 2); i++)
    {
        txt[cursorAt] = (i % 2 == 0) ? ' ' : '_';
        print(txt, BLINK_DELAY, BRIGHTNESS_MAX);
    }
}

void Display::pause(byte seconds)
{
    print(BLANK_DISPLAY, seconds * 1000, BRIGHTNESS_MIN);
}

string Display::alignCenter(string txt)
{
    int size = txt.length();
    if (size >= DISPLAY_SIZE)
    {
        return txt;
    }
    byte n = (DISPLAY_SIZE - size) / 2;
    if ((DISPLAY_SIZE - size) % 2 == 0)
    {
        txt = blankText(n) + txt;
    }
    else
    {
        txt = blankText(n + 1) + txt;
    }
    return txt + blankText(n);
}

string Display::alignRight(string txt)
{
    int size = txt.length();
    if (size >= DISPLAY_SIZE)
    {
        return txt;
    }
    return blankText(DISPLAY_SIZE - size) + txt;
}

string Display::alignLeft(string txt)
{
    int size = txt.length();
    if (size >= DISPLAY_SIZE)
    {
        return txt;
    }
    return txt + blankText(DISPLAY_SIZE - size);
}

string Display::alignJustify(string txt)
{
    int size = txt.length();
    if (size >= DISPLAY_SIZE)
    {
        return txt;
    }
    if (txt.find_first_of(BLANK_CHAR) != txt.find_last_of(BLANK_CHAR))
    {
        // justifies only two words separated by one single blank!
        return txt;
    }
    txt.replace(txt.find_first_of(BLANK_CHAR), 1, blankText(DISPLAY_SIZE - size + 1));
    return txt;
}

void Display::setBrightness(byte brightness)
{
    if (this->currentBrightness != brightness)
    {
        writeByte(BRIGHTNESS_MASK | brightness);
        this->currentBrightness = brightness;
    }
}

void Display::writeChar(char aChar)
{
    writeByte(getChar(aChar));
}

char Display::getChar(char c)
{
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
    for (int i = 0; i < 8; i++)
    {
        bool bit = (((aByte >> (7 - i)) & 0x01) == 1);
        writeBit(bit);
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
    digitalWrite(this->data, LOW);
    digitalWrite(this->sclk, LOW);
    digitalWrite(this->rset, LOW);
    delay(RESET_DELAY);
    digitalWrite(this->rset, HIGH);
    delay(RESET_DELAY);
}

void Display::init()
{
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
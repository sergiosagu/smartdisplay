#include <string>

using namespace std;

typedef unsigned char byte;

// MAGIC NUMBERS

const byte BRIGHTNESS_MASK = 0b11100000;
const byte COUNTER_MASK = 0b11000000;
const byte POINTER_MASK = 0b10100000;

const byte COUNTER_CONTROL = COUNTER_MASK | 0;  // # of chars (0 = all)
const byte POINTER_CONTROL = POINTER_MASK | 15; // start from the left

const byte RESET_DELAY = 5;  // millis 2
const byte CHAR_DELAY = 125; // millis

const byte BIT_DELAY = 5;   // micros 2
const byte HIGH_DELAY = 15; // micros 10
const byte LOW_DELAY = 10;  // micros 5

// CONSTANTS

const byte BRIGHTNESS_MIN = 0;  // 0 = 0%, 1 = 3%
const byte BRIGHTNESS_MAX = 25; // 25 = 80%, 31 = 100%

const string BLANK_CHAR = " ";
const string BLANK_DISPLAY = "                ";

const byte DISPLAY_SIZE = 16;

const byte SLIDE_DELAY = 125; // millis

const byte FADE_DELAY = 10; // millis

const byte BLINK_DELAY = 250; // millis

const byte CRACK_DELAY = 50; // millis
const byte CRACK_NOISE = 4;  // # of rounds per char

const byte TERM_DELAY = 125; // millis
const byte TERM_BLINK = 4;   // # of cursor blinks

class Display
{
private:
    byte id;
    string name;
    byte sclk;
    byte data;
    byte rset;
    volatile byte currentBrightness = -1;

public:
    Display(string name, byte sclk, byte data, byte rset);
    ~Display();

    void demo();
    void print(string msg, int millis, byte brightness);
    void fadeIn(string msg);
    void fadeOut(string msg);
    void fadeBlink(string msg);
    void blink(string msg);
    void slideLeft(string msg);
    void slideRight(string msg);
    void crack(string msg);
    void term(string msg);
    void pause(byte seconds);

    void reset();
    void init();

    static void libSetup();

    static string alignCenter(string txt);
    static string alignRight(string txt);
    static string alignLeft(string txt);
    static string alignJustify(string txt);

protected:
    void setBrightness(byte brightness);
    void writeChar(char aChar);
    virtual char getChar(char c);
    void writeByte(byte aByte);
    void writeBit(bool aBit);

    virtual char randomChar();
    string randomText(byte size);
    static string blankText(byte size);
};

class DotDisplay : public Display
{
public:
    DotDisplay(string name, byte sclk, byte data, byte rset);
    ~DotDisplay();

protected:
    char getChar(char c) override;
    char randomChar() override;
};
#include <thread>
#include "displays.hpp"
#include "providers.hpp"

void topThread(Display d)
{
    // string ip;
    // ip = Display::alignCenter(Provider::getIp());
    for (;;)
    {
        // d.fadeBlink(ip);
        d.demo();
        // d.fadeBlink(Display::alignCenter(Provider::getTime()));
    }
}

void midThread(Display d)
{
    for (;;)
    {
        d.demo();
        // d.fadeBlink(Display::alignCenter(Provider::getDate()));
    }
}

void botThread(Display d)
{
    for (;;)
    {
        d.demo();
        // d.fadeBlink(Display::alignCenter(Provider::getDateTime()));
    }
}

int main(int argc, char const *argv[])
{
    srand(time(nullptr)); // init random generator

    Display::libSetup();

    // DotDisplay d1("top", 10, 9, 11);
    Display d1("top", 10, 9, 11);
    d1.init();

    Display d2("mid", 17, 27, 22);
    d2.init();

    Display d3("bot", 2, 3, 4);
    d3.init();

    // string ip;
    // ip = Display::alignCenter(Provider::getIp());
    // ip = Provider::getIp();
    // ip = "192:168:1:123";

    string txt = "Quick Demo";
    string msg = Display::alignCenter(txt);

    for (;;)
    {
        // d1.slideLeft(ip);
        // d2.slideLeft(ip);
        // d3.slideLeft(ip);

        // d1.print(Display::alignCenter(Provider::getTime()), 1000, BRIGHTNESS_MAX);
        // d2.print(Display::alignCenter(Provider::getDate()), 1000, BRIGHTNESS_MAX);
        // d3.print(Display::alignCenter(Provider::getDateTime()), 1000, BRIGHTNESS_MAX);

        d1.demo();
        d2.demo();
        d3.demo();

        // d1.crack(msg);
        // d1.print(msg, 2000, BRIGHTNESS_MAX);
        // d1.pause(1);
        // d2.crack(msg);
        // d2.print(msg, 2000, BRIGHTNESS_MAX);
        // d2.pause(1);
        // d3.crack(msg);
        // d3.print(msg, 2000, BRIGHTNESS_MAX);
        // d3.pause(1);
    }

    // thread t1(topThread, d1);
    // thread t2(midThread, d2);
    // thread t3(botThread, d3);

    // t1.join();
    // t2.join();
    // t3.join();

    return 0;
}

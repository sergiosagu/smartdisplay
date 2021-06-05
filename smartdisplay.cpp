#include <thread>
#include "displays.hpp"
#include "providers.hpp"

void topThread(Display d)
{
    string ip;
    ip = Display::alignCenter(Provider::getIp());
    for (;;)
    {
        d.fadeBlink(ip);
        // d.demo();
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

    Display d1("top", 10, 9, 11);
    d1.init();

    Display d2("mid", 2, 3, 4);
    d2.init();

    Display d3("bot", 17, 27, 22);
    d3.init();

    // for (;;)
    // {
    // d1.slideLeft(Display::alignCenter(Provider::getTime()));
    // d2.slideLeft(Display::alignCenter(Provider::getDate()));
    // d3.slideLeft(Display::alignCenter(Provider::getDateTime()));

    // d1.print(Display::alignCenter(Provider::getTime()), 1000, BRIGHTNESS_MAX);
    // d2.print(Display::alignCenter(Provider::getDate()), 1000, BRIGHTNESS_MAX);
    // d3.print(Display::alignCenter(Provider::getDateTime()), 1000, BRIGHTNESS_MAX);

    // d1.print(Provider::getIp(), 1000, BRIGHTNESS_MAX);
    // d1.demo();
    // d2.demo();
    // d3.demo();
    // }

    thread t1(topThread, d1);
    thread t2(midThread, d2);
    thread t3(botThread, d3);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

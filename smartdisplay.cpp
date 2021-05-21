#include "displays.hpp"

int main(int argc, char const *argv[])
{
    Display::libSetup();

    // Display d1(1, 2, 3);
    Display d1(10, 9, 11);

    d1.init();

    for (;;)
    {
        d1.demo();
    }

    return 0;
}

#include "displays.hpp"

int main(int argc, char const *argv[])
{
    srand(time(nullptr)); // init random generator

    Display::libSetup();

    // Display d1(2, 3, 4);
    // Display d1(17, 27, 22);
    Display d1(10, 9, 11);

    d1.init();

    for (;;)
    {
        d1.demo();
    }

    return 0;
}

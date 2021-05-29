# Smart Display
My attempt to build a useful-ish DIY smart device with few components which I have had hanging around for a while:
- A **Raspberry Pi Zero W** (using the WiringPi library)
- A **Samsung 16LF01UA3** VFD Module (16-segment 16 characters)
- A **Futaba M16MY02A** VFD Module (14-segments 16 characters)
- A **Noritake GU96x8M-K609C1** VFD Module (96x8 graphic dot matrix)
- The bare minimum electronics to interconnect those with each other :-)
## Components
### displays.hpp displays.cpp
These define the interface and implementation related to the VFD modules. Essentially, they provide the functionality to display the data in different ways. Some examples are:
- Print a message.
- Slide a text left-to-right and right-to-left.
- Blink a message.
- Fade-in, fade-out and blink with fade effect a message.
- "Crack" a message, like deciphering it.
- Print a text like in a terminal.
### providers.hpp providers.cpp
These define the interface and implementation related to the providers of the data that will be displayed. Essentially, they provide the functionality to retrieve different data from different sources. Some examples are:
- Date and time
- Weather
- Quote of the day
- Stocks
- Push messages
### smartdisplay.cpp
Main application combining the previous functionality.
## Build & Run
Build the project (no WiringPi library needed)
```
$ make
```
Push the sources to your Raspberry Pi (to `/root/smartdisplay/`)
```
$ make push RPI_IP=172.16.0.1
```
Build the project from your Raspberry Pi (WiringPi library needs to be installed)
```
$ make RPI=true
```
Run the project
```
$ ./smartdisplay
```
Clean the project
```
$ make clean
```
## Result
*Coming soon!*
# Related work
This project is an evolution of https://github.com/sergiosagu/arduino

## Scratchpad
Turn on the built-in led
```
$ echo 255 | sudo tee /sys/class/leds/led0/brightness
```
Turn off the built-in led
```
$ echo 0 | sudo tee /sys/class/leds/led0/brightness
```
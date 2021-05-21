CC = g++

ifdef RPI
CFLAGS = -Wall -pthread -lwiringPi
WPIFLAG = -DWPI
else
CFLAGS = -Wall -pthread
WPIFLAG =
endif

default: smartdisplay

smartdisplay: smartdisplay.o displays.o
	$(CC) $(CFLAGS) -o smartdisplay smartdisplay.o displays.o

smartdisplay.o: smartdisplay.cpp
	$(CC) $(CFLAGS) -c smartdisplay.cpp

displays.o: displays.cpp displays.hpp
	$(CC) $(CFLAGS) -c displays.cpp $(WPIFLAG)

clean:
	$(RM) smartdisplay *.o *~ *.h*.gch

push:
	@echo "RPI_IP='"$(RPI_IP)"'"
	scp Makefile *.hpp *.cpp root@$(RPI_IP):~/smartdisplay/
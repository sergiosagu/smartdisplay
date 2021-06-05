CC = g++

ifdef RPI
CFLAGS = -Wall -pthread
WPIFLAG = -DWPI
LDFLAGS = -lwiringPi
else
CFLAGS = -Wall -pthread -g
WPIFLAG =
LDFLAGS = -lncurses
endif

default: smartdisplay

smartdisplay: smartdisplay.o displays.o providers.o
	$(CC) $(CFLAGS) -o smartdisplay smartdisplay.o displays.o providers.o $(LDFLAGS)

smartdisplay.o: smartdisplay.cpp
	$(CC) $(CFLAGS) -c smartdisplay.cpp

displays.o: displays.cpp displays.hpp
	$(CC) $(CFLAGS) -c displays.cpp $(WPIFLAG) 

providers.o: providers.cpp providers.hpp
	$(CC) $(CFLAGS) -c providers.cpp -ljsoncpp -lcurl

clean:
	$(RM) smartdisplay *.o *~ *.h*.gch

push:
	@echo "RPI_IP='"$(RPI_IP)"'"
	scp Makefile *.hpp *.cpp root@$(RPI_IP):~/smartdisplay/
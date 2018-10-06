all: dell-brightness

clean:
	rm dell-brightness
	rm *.o

dell-brightness: main.o
	g++ -lusb-1.0 -lDellMonitorSdkSo -o dell-brightness main.o

main.o: main.cpp
	g++ -c main.cpp

CC      = g++

all: main

main: main.cpp
	$(CC) *.cpp *.h -o app `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm app

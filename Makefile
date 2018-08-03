CC      = g++

all: basic

basic: basic.cpp
	$(CC) basic.cpp -o basic `pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm basic

CC      = g++
SOURCE_FILES = *.cpp *.h
all: main

main: main.cpp
	$(CC) $(SOURCE_FILES) -g `pkg-config --cflags gtk+-3.0 gtkmm-3.0` -o vpl_wexecution `pkg-config --libs gtk+-3.0 gtkmm-3.0` -rdynamic -lstdc++ -std=c++11 -lm

clean:
	rm vpl_wexecution

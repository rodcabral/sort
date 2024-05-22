CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address
INCLUDE = -Iinclude
LIBS = -lSDL2 -lSDL2_ttf

all: build
	$(CC) $(CFLAGS) main.c $(INCLUDE) src/visualizer.c -o build/visualizer $(LIBS)

build:
	mkdir build

clean:
	rm -rf build

CC = gcc
CFLAGS = -Wall -Wextra -fno-stack-protector -O3
INCLUDE = -Iinclude
LIBS = -lSDL2 -lSDL2_ttf

all: build
	$(CC) $(CFLAGS) main.c $(INCLUDE) src/visualizer.c src/sort.c src/utils.c -o build/visualizer $(LIBS)

build:
	mkdir build

clean:
	rm -rf build

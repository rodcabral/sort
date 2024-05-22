CC = gcc
CFLAGS = -Wall -Wextra -fsanitize=address
LIBS = -lSDL2 -lSDL2_ttf

all: build
	$(CC) $(CFLAGS) main.c src/visualizer.c -o build/visualizer $(LIBS)

build:
	mkdir build

clean:
	rm -rf build

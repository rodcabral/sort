CFLAGS = -Wall -Wextra
LIBS = -lSDL2 -lSDL2_ttf

visualizer: $(wildcard src/*.c include/*.h)
	$(CC) $(FLAGS) main.c $(wildcard src/*.c) -Iinclude $(LIBS) -o visualizer

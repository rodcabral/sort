FLAGS = -O2
LIBS = -lSDL3 -lSDL3_ttf

sort: main.c $(wildcard ./include/*.h ./src/*.c)
	$(CC) $(FLAGS) $(LIBS) $(wildcard ./src/*.c) main.c -o sort

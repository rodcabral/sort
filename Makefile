FLAGS = -Wall -Wextra -fsanitize=address
LIBS = -lSDL3

all: main.c $(wildcard ./include/*.h ./src/*.c)
	$(CC) $(FLAGS) $(LIBS) $(wildcard ./src/*.c) main.c -o sort

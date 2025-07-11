FLAGS = -Wall -Wextra -fsanitize=address

all: main.c $(wildcard ./include/*.h ./src/*.c)
	$(CC) $(FLAGS) $(wildcard ./src/*.c) main.c -o sort

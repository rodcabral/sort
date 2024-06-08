CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lSDL2 -lSDL2_ttf

OBJ = ./build/obj

all: build visualizer app

visualizer: \
	$(OBJ)/sort.o \
	$(OBJ)/visualizer.o \
	$(OBJ)/utils.o \

app: $(OBJ)/sort.o $(OBJ)/visualizer.o $(OBJ)/utils.o
	$(CC) $(CFLAGS) -O3 main.c $(OBJ)/*.o -Iinclude $(LIBS) -o ./build/visualizer

$(OBJ)/%.o: ./src/%.c
	gcc -O3 -c $< -Iinclude -o $@

build:
	mkdir build
	mkdir build/obj

clean:
	rm -rf build

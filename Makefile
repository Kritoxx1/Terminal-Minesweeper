CC = gcc
SRC = menu.c game.c main.c
LINK = -lncurses
TARGET = minesweeper
FLAGS = -Wall

all:
	mkdir -p Build
	$(CC) $(SRC) -o Build/$(TARGET) $(LINK) $(FLAGS)

run:
	./Build/$(TARGET)

clean:
	rm -rf Build/$(TARGET)
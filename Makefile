CC = gcc
SRC = startMenu.c game.c gameOverMenu.c main.c
LINK = -lncurses
TARGET = minesweeper
FLAGS = -Wall

all:
	$(CC) $(SRC) -o $(TARGET) $(LINK) $(FLAGS)

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET)
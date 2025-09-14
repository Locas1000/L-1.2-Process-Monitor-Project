CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -O2
SRC=src/main.c
BIN=main

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	rm -f $(BIN)

.PHONY: all clean

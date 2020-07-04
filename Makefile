CFLAGS=-O2 -Wall -Wextra -pedantic -Wno-vla -std=c11
SRCS=src/screen.c
HEADS=src/tetris.h
OBJS=$(SRCS:.c=.o)
LDFLAGS=-lncurses -lm

tetris: $(SRCS) $(HEADS)
	$(CC) $(CFLAGS) $(SRCS) -o $@ $(LDFLAGS)

clean:
	rm -rf tetris src/*.o

.PHONY: test clean

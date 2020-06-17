CC = gcc
CFLAGS = -g -Wall -Werror
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXE = test_graphe

all: $(EXE)

test_graphe: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o : %.c
	$(CC) $(CFLAGS) -c $<

pile.o : pile.h graphe.h
file.o : file.h graphe.h
graphe.o : graphe.h
test_graphe.o : graphe.h
io_graphe.o : graphe.h

clean:
	rm -f $(OBJ) $(EXE)  *~ data/*~
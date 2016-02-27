# a Makefile devmem.c


EXE=ahci
CC=gcc
CFLAGS=-c -g
LDFLAGS=
SRC=$(EXE).c
OBJ=$(SRC:.c=.o)

all: $(SRC) $(EXE)
	
$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXE) $(EXE).o

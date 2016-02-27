# a Makefile devmem.c


EXE=ahci_tst
CC=gcc
CFLAGS=-c -g
LDFLAGS=
SRC=$(EXE).c ahci.c
OBJ=$(SRC:.c=.o)

all: $(SRC) $(EXE)
	
$(EXE): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXE) *.o

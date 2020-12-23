CC := gcc
CFLAGS := -g -Wall -Werror -DCSV
LFLAGS := -lm


SRC := $(wildcard *.c)
OBJ := $(SRC:%.c=%.o)
EXE := main.x

.PHONY:all clean run

all: $(EXE)

%.x:
	$(CC) $^ -o $@ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


run: all
	./$(EXE)

clean:
	rm -f *.o *.x

CA:
	rm -rf *.o *.x *.dat data/

main.x: main.o

CC := gcc
CFLAGS := -g -Wall -Werror
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


run:
	./$(EXE)

clean:
	rm -f *.o *.x

CA:
	rm -rf *.o *.x *.dat

main.x: main.o

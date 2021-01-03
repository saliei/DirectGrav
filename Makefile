CC       := gcc
CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -g -O3 -Wall -Werror
LDFLAGS  := -Llib
LDLIBS   := -lm

SRCDIR := src
OBJDIR := obj
BINDIR := build

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

EXE := $(BINDIR)/main.x

.PHONY:all clean run

all: $(EXE)

$(EXE): $(OBJ) | $(BINDIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJDIR) $(BINDIR):
	mkdir -p $@
	@cp "params.in" $(BINDIR)

run: all
	./$(EXE)

clean:
	@$(RM) -rv $(BINDIR) $(OBJDIR)

-include $(OBJ:.o=.d)

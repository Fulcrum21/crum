CC=clang
CFLAGS =-ggdb -Wall -Wextra -flto
SRCDIR=src
OBJDIR=obj
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

crum: $(OBJ)
	$(CC) -o $@ $^ -lm $(CFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $(CFLAGS) $^
clean:
	$(RM) $(OBJDIR)/* crum

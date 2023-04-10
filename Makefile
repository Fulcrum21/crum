CC=clang
CFLAGS =-ggdb -Wall -Wextra

crum: crum.c stack.c
	$(CC) $(CFLAGS) -o $@ $^

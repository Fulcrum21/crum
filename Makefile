CC=clang
CFLAGS =-ggdb -Wall -Wextra

crum: crum.c stack.c main.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

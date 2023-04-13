CC=clang
CFLAGS =-ggdb -Wall -Wextra

crum: crum.c stack.c main.c slice.c
	$(CC) $(CFLAGS) -o $@ $^ -lm

CC=clang
CFLAGS =-g -Wall

crum: main.c
	$(CC) $(CFLAGS) -o $@ $^

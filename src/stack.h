#include <stdbool.h>
#include <stddef.h>
#ifndef STACK_H_
#define STACK_H_
#define STACK_CAPACITY 100
typedef struct
{
	long double nums[STACK_CAPACITY];
	size_t stack_size;
} Stack;

void print_Stack(Stack stack);
void push_Stack(Stack* stack, long double num);
long double pop_Stack(Stack* stack);
#endif // STACK_H_

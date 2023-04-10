#include <stdbool.h>
#include <stddef.h>
#ifndef STACK_H_
#define STACK_H_
#define STACK_SIZE 100
typedef struct
{
	long double nums[STACK_SIZE];
	size_t stack_size;
} Stack;

Stack init_Stack();
bool push_Stack(Stack* stack, long double num);
long double pop_Stack(Stack* stack);
#endif // STACK_H_

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#define STACK_SIZE 100
typedef struct
{
	long double nums[STACK_SIZE];
	size_t stack_size;
} Stack;

Stack init_Stack()
{
	Stack x;
	x.stack_size = 0;
	return x;
}

bool push_Stack(Stack* stack, long double num)
{
	assert(stack != NULL);
	if ( stack->stack_size >= STACK_SIZE )
	{
		return false;
	}
	stack->nums[stack->stack_size] = num;
	stack->stack_size++;
	return true;
}

long double pop_Stack(Stack* stack)
{
	assert(stack != NULL);
	if ( stack->stack_size == 0 )
	{
		return NAN;
	}
	stack->stack_size--;
	long double num = stack->nums[stack->stack_size];
	return num;
}

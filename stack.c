#include "stack.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void push_Stack(Stack* stack, long double num)
{
	assert(stack != NULL);
	if ( stack->stack_size >= STACK_CAPACITY )
	{
		fprintf(stdout, "Couldnt push number, stack is too full");
		return;
	}
	stack->nums[stack->stack_size] = num;
	stack->stack_size++;
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

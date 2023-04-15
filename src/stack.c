#include "stack.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void print_Stack(Stack stack)
{
	size_t n = stack.stack_size;
	if ( n == 0 )
	{
		puts("The stack is empty");
		return;
	}

	puts("Stack from top to bottom:");
	size_t i;
	for ( i = 0; i < n - 1; i++ )
	{
		printf("%.11Lg, ", stack.nums[n - i - 1]);
	}
	printf("%.11Lg\n", stack.nums[n - i - 1]);
}

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
	// if ( stack->stack_size == 0 )
	// {
	// 	return NAN;
	// }
	stack->stack_size--;
	long double num = stack->nums[stack->stack_size];
	return num;
}

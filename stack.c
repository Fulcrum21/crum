#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	long double* nums;
	size_t stack_size;
	size_t capacity;
} Stack;

Stack init_Stack_capacity(size_t capacity)
{
	Stack x;
	x.stack_size = 0;
	x.capacity = capacity;
	x.nums = malloc(capacity * sizeof(Stack));
	if ( x.nums == NULL )
	{
		perror("Failed to malloc stack due to error");
		exit(1);
	}
	return x;
}

Stack init_Stack()
{
#define STACK_SIZE 100
	return init_Stack_capacity(STACK_SIZE);
#undef STACK_SIZE
}

void push_Stack(Stack* stack, long double num)
{
	assert(stack != NULL);
	if ( stack->stack_size >= stack->capacity )
	{
		stack->capacity += 64;
		stack->nums = realloc(stack->nums, stack->capacity);
		if ( stack->nums == NULL )
		{
			perror("Failed to realloc stack due to");
			exit(1);
		}
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

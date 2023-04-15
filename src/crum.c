#include "crum.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern bool use_radians;

void print_stack_top(Stack stack)
{
	if ( stack.stack_size == 0 )
	{
		puts("The stack is empty");
		return;
	}
	printf("%.11Lg\n", stack.nums[stack.stack_size - 1]);
}
#define deg_to_rad(deg) ((deg) / 180.0L * M_PI)

void evaluate_string(Stack* stack, Slice input)
{
	if ( stack == NULL )
	{
		fputs("stack variable is NULL\n", stderr);
		exit(1);
	}
	for ( size_t i = 0; i < input.size; i++ )
	{
		char c = input.string[i];
		if ( isspace(c) )
		{
			continue;
		}
		char* end_of_num;
		long double num = strtold(input.string + i, &end_of_num);
		if ( end_of_num != input.string + i )
		{
			push_Stack(stack, num);
			i = end_of_num - input.string - 1;
		}
		else if ( c == '+' || c == '-' || c == '/' || c == '*' || c == '%' )
		{
			if ( stack->stack_size < 2 )
			{
				puts("Not enough arguments in stack to perform the operation");
			}
			long double operand1 = pop_Stack(stack);
			long double operand2 = pop_Stack(stack);
			switch ( c )
			{
				case '+':
					push_Stack(stack, operand2 + operand1);
					break;
				case '-':
					push_Stack(stack, operand2 - operand1);
					break;
				case '*':
					push_Stack(stack, operand2 * operand1);
					break;
				case '/':
					if ( operand1 == 0.0l )
					{
						fputs("Attemped to divide by zero, invalid operation\n", stderr);
						exit(1);
					}
					push_Stack(stack, operand2 / operand1);
					break;
				case '%':
					if ( operand1 == 0.0l )
					{
						fputs("Attemped to divide by zero, invalid operation\n", stderr);
						exit(1);
					}
					push_Stack(stack, fmodl(operand2, operand1));
					break;
			}
		}
		else
		{
#define TEMP_SIZE 4
			char temp[TEMP_SIZE] = { 0 };
			int j = 0;
			size_t k = i;
			while ( j < TEMP_SIZE && isalpha(input.string[k]) )
			{
				temp[j] = input.string[k];
				k++;
				j++;
			}
#undef TEMP_SIZE
			if ( strcmp(temp, "d") == 0 )
			{
				if ( stack->stack_size > 0 )
				{
					push_Stack(stack, stack->nums[stack->stack_size - 1]);
				}
				else
				{
					puts("No numbers in stack to duplicate");
					break;
				}
			}
			if ( strcmp(temp, "t") == 0 )
			{
				print_stack_top(*stack);
			}
			else if ( strcmp(temp, "o") == 0 )
			{
				if ( stack->stack_size == 0 )
				{
					puts("Nothing to pop off the stack");
					break;
				}
				long double popped = pop_Stack(stack);
				printf("%Lf\n", popped);
			}
			else if ( strcmp(temp, "c") == 0 )
			{
				stack->stack_size = 0;
			}
			else if ( strcmp(temp, "s") == 0 )
			{
				if ( stack->stack_size >= 2 )
				{
					long double temp = stack->nums[stack->stack_size - 1];
					stack->nums[stack->stack_size - 1] = stack->nums[stack->stack_size - 2];
					stack->nums[stack->stack_size - 2] = temp;
				}
				else
				{
					puts("Not enough elements in stack to swap");
					break;
				}
			}
			else if ( strcmp(temp, "p") == 0 )
			{
				print_Stack(*stack);
			}
			else if ( strcmp(temp, "pi") == 0 )
			{
				push_Stack(stack, M_PI);
			}
			else if ( strcmp(temp, "tau") == 0 )
			{
				push_Stack(stack, 2.0L * M_PI);
			}
			else if ( strcmp(temp, "sin") == 0 )
			{
				if ( stack->stack_size == 0 )
				{
					puts("Not enough arguments in stack to perform operation sin");
					break;
				}
				long double degrees = pop_Stack(stack);
				if ( !use_radians )
				{
					degrees = deg_to_rad(degrees);
				}
				push_Stack(stack, sinl(degrees));
			}
			else if ( strcmp(temp, "cos") == 0 )
			{
				if ( stack->stack_size == 0 )
				{
					puts("Not enough arguments in stack to perform operation cos");
					break;
				}
				long double degrees = pop_Stack(stack);
				if ( !use_radians )
				{
					degrees = deg_to_rad(degrees);
				}
				push_Stack(stack, cosl(degrees));
			}
			else if ( strcmp(temp, "tan") == 0 )
			{
				if ( stack->stack_size == 0 )
				{
					puts("Not enough arguments in stack to perform operation tan");
					break;
				}
				long double degrees = pop_Stack(stack);
				if ( !use_radians )
				{
					degrees = deg_to_rad(degrees);
				}
				if ( degrees == M_PI / 2 )
				{
					puts("Tan is not defined at pi/2");
				}
				else
				{
					push_Stack(stack, cosl(degrees));
				}
			}
			else
			{
				fprintf(stderr, "Found an illegal token at index %lu: %s\n", i + 1, temp);
				return;
			}
			i = k - 1;
		}
	}
}

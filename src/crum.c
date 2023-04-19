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

Result evaluate_string(Stack* stack, Slice input)
{
	if ( stack == NULL )
	{
		fputs("stack variable is NULL\n", stderr);
		exit(1);
	}
	size_t n = input.size;
	for ( size_t i = 0; i < n; i++ )
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
				return create_Result_err("Not enough arguments in stack to perform operation", 1, i);
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
						push_Stack(stack, operand2);
						push_Stack(stack, operand1);
						return create_Result_err("Attemped to divide by zero, invalid operation\n", 1, i);
					}
					push_Stack(stack, operand2 / operand1);
					break;
				case '%':
					if ( operand1 == 0.0l )
					{
						push_Stack(stack, operand2);
						push_Stack(stack, operand1);
						return create_Result_err("Attemped to Modulo by zero, invalid operation\n", 1, i);
					}
					push_Stack(stack, fmodl(operand2, operand1));
					break;
			}
		}
		else
		{
#define TEMP_SIZE 5
			char temp[TEMP_SIZE] = { 0 };
			int j = 0;
			size_t k = i;
			while ( i < n && j < TEMP_SIZE && isalpha(input.string[i]) )
			{
				temp[j] = input.string[i];
				i++;
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
					return create_Result_err("No items on the stack to duplicate", j, k);
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
					return create_Result_err("No items to on the stack to be popped", j, k);
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
					return create_Result_err("Not enough items in the stack to swap top two elements", j, k);
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
					return create_Result_err("Not enough items to do operation", j, k);
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
					return create_Result_err("Not enough items to do operation", j, k);
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
					return create_Result_err("Not enough items to do operation", j, k);
				}
				long double degrees = pop_Stack(stack);
				if ( !use_radians )
				{
					degrees = deg_to_rad(degrees);
				}
				else
				{
					push_Stack(stack, tanl(degrees));
				}
			}
			else if ( strcmp(temp, "sqrt") == 0 )
			{
				if ( stack->stack_size == 0 )
				{
					return create_Result_err("No items on stack to perform operation", j, k);
				}
				long double popped = pop_Stack(stack);
				if ( popped < 0 )
				{
					return create_Result_err("Attempted to take square root of negative number", j, k);
					push_Stack(stack, popped);
				}
				push_Stack(stack, sqrtl(popped));
			}
			else
			{
				return create_Result_err("Found an illegal token", j, k);
			}
		}
	}
	if ( stack->stack_size == 0 )
	{
		return create_Result(0.0L);
	}
	else
	{
		return create_Result(stack->nums[stack->stack_size - 1]);
	}
}

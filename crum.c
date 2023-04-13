#include "crum.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_stack_top(Stack stack)
{
	if ( stack.stack_size == 0 )
	{
		puts("The stack is empty");
		return;
	}
	printf("%.4Lf\n", stack.nums[stack.stack_size - 1]);
}

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
			if ( end_of_num >= input.string + input.size )
			{
				break;
			}
		}
		else if ( c == '+' || c == '-' || c == '/' || c == '*' || c == '%' )
		{
			long double operand1 = pop_Stack(stack);
			if ( isnan(operand1) )
			{
				fputs("Stack is empty, failed to pop a number\n", stderr);
				exit(1);
			}
			long double operand2 = pop_Stack(stack);
			if ( isnan(operand2) )
			{
				fputs("Stack is empty, failed to pop a number\n", stderr);
				exit(1);
			}
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
				default:
					fprintf(stderr, "Found an illegal character at index %lu: %c\n", i + 1, input.string[i]);
			}
			continue;
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
			if ( strcmp(temp, "p") == 0 )
			{
				print_stack_top(*stack);
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
				long double degrees = pop_Stack(stack);
				if ( isnan(degrees) )
				{
					fputs("Stack is empty, failed to pop a number\n", stderr);
					exit(1);
				}
				push_Stack(stack, sinl(degrees));
			}
			else
			{
				fprintf(stderr, "Found an illegal token at index %lu: %s\n", i + 1, temp);
				return;
			}
			i = k - 1;
		}

#undef TEMP_SIZE
	}
}

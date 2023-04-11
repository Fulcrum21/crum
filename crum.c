#include "./stack.h"
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

void evaluate_string(Stack* stack, const char* input)
{
	if ( strcmp(input, "") == 0 )
	{
		fprintf(stderr, "Empty input string, can't calculate anything\n");
		return;
	}
	if ( stack == NULL )
	{
		fputs("stack variable is NULL\n", stderr);
		exit(1);
	}
	char c;
	for ( size_t i = 0; (c = input[i]) != '\0'; i++ )
	{
		if ( isspace(c) )
		{
			continue;
		}
		char* end_of_num;
		long double num = strtold(input + i, &end_of_num);
		if ( end_of_num != input + i )
		{
			push_Stack(stack, num);
			i = end_of_num - input - 1;
			continue;
		}
		if ( c == '+' || c == '-' || c == '/' || c == '*' || c == '%' )
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
					fprintf(stderr, "Found an illegal character at index %lu: %c\n", i + 1, input[i]);
			}
			continue;
		}
#define TEMP_SIZE 4
		char temp[TEMP_SIZE] = { 0 };
		int j = 0;
		size_t k = i;
		while ( j < TEMP_SIZE && isalpha(input[k]) )
		{
			temp[j] = input[k];
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
		else
		{
			fprintf(stderr, "Found an illegal token at index %lu: %s\n", i + 1, temp);
			return;
		}
		i = k - 1;

#undef TEMP_SIZE
	}
}

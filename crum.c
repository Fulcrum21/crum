#include "./stack.h"
#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long double evaluate_string(const char* input)
{
	if ( strcmp(input, "") == 0 )
	{
		fprintf(stderr, "Empty input string, can't calculate anything\n");
		exit(1);
	}
	Stack stack = init_Stack();
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
			if ( !push_Stack(&stack, num) )
			{
				fputs("Stack is full, couldn't push a number", stderr);
				exit(1);
			}
			i = end_of_num - input - 1;
		}
		else
		{
			switch ( c )
			{
				case '+':
					{
						long double operand1 = pop_Stack(&stack);
						if ( isnan(operand1) )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						long double operand2 = pop_Stack(&stack);
						if ( isnan(operand2) )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						push_Stack(&stack, operand2 + operand1);
						break;
					}
				case '-':
					{
						long double operand1 = pop_Stack(&stack);
						if ( isnan(operand1) )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						long double operand2 = pop_Stack(&stack);
						if ( isnan(operand2) )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						push_Stack(&stack, operand2 - operand1);
						break;
					}
				case '*':
					{
						long double operand1 = pop_Stack(&stack);
						if ( isnan(operand1) )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						long double operand2 = pop_Stack(&stack);
						if ( isnan(operand2) )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						push_Stack(&stack, operand2 * operand1);
						break;
					}
				case '/':
					{
						long double operand1 = pop_Stack(&stack);
						if ( isnan(operand1) )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						if ( operand1 == 0.0l )
						{
							fputs("Attemped to divide by zero, invalid operation\n", stderr);
							exit(1);
						}
						long double operand2 = pop_Stack(&stack);
						if ( isnan(operand2) )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						push_Stack(&stack, operand2 / operand1);
						break;
					}
				default:
					{
						fprintf(stderr, "Found an illegal character at index %lu: %c\n", i + 1, input[i]);
						break;
					}
			}
		}
	}
	return pop_Stack(&stack);
}

int main(int argc, char* argv[])
{
	// const char* input1 = "1 2 - 4 5 + *";
	// printf("%.3Lg\n", evaluate_string(input1));
	const char* input2 = "0.0 0.0 /";
	printf("%.3Lg\n", evaluate_string(input2));
	return EXIT_SUCCESS;
}

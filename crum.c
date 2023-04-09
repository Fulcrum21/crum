#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STACK_SIZE 100

typedef enum {
	TOKEN_OP,
	TOKEN_NUM,
} Token_Type;

typedef struct
{
	union
	{
		long double num;
		char op;
	};
	Token_Type type;
} Token;

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
		return LDBL_MIN;
	}
	stack->stack_size--;
	long double num = stack->nums[stack->stack_size];
	return num;
}

int main(int argc, char* argv[])
{
	Stack stack = init_Stack();
	const char* input = "1.2 2.4 3.5 /\n";
	char c;
	for ( size_t i = 0; (c = input[i]) != '\0'; i++ )
	{
		if ( c == ' ' || c == '\t' )
		{
			continue;
		}
		if ( isdigit(c) )
		{
			char* end_of_num;
			long double num = strtold(input + i, &end_of_num);
			if ( push_Stack(&stack, num) == false )
			{
				fputs("Stack is full, push a number", stderr);
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
						if ( operand1 == LDBL_MIN )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						long double operand2 = pop_Stack(&stack);
						if ( operand2 == LDBL_MIN )
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
						if ( operand1 == LDBL_MIN )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						long double operand2 = pop_Stack(&stack);
						if ( operand2 == LDBL_MIN )
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
						if ( operand1 == LDBL_MIN )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						long double operand2 = pop_Stack(&stack);
						if ( operand2 == LDBL_MIN )
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
						if ( operand1 == LDBL_MIN )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						long double operand2 = pop_Stack(&stack);
						if ( operand2 == LDBL_MIN )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						push_Stack(&stack, operand2 / operand1);
						break;
					}
				case '\n':
					{
						long double popped_num = pop_Stack(&stack);
						if ( popped_num == LDBL_MIN )
						{
							fputs("Stack is empty, failed to pop a number\n", stderr);
							exit(1);
						}
						printf("%.8Lg\n", popped_num);
						break;
					}
				default:
					{
						fprintf(stderr, "Found an illegal character at index %lu: %c\n", i + 1, input[i]);
					}
			}
		}
	}

	return EXIT_SUCCESS;
}

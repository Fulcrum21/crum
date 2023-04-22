#include "crum.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern bool use_radians;

typedef enum { ADD, SUBTRACT, MULTIPLY, DIVIDE, MODULO } Operation;

// Performs the operation op on the stack, and stores the result of the calculation
// in the pointer result
// this returns true if the calculation was successful, and false otherwise
// if false is returned, check the value inside the result pointer for the error
// result = INFINITY: there are less than two items in the stack
// result = 0.0: the denominator in the division and modulo operations is zero
bool perform_operation(Operation op, Stack* stack, long double* result);

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

Result evaluate_string(Stack* stack, Slice tokens[], size_t token_length)
{
	if ( stack == NULL )
	{
		fputs("stack variable is NULL\n", stderr);
		exit(1);
	}
	size_t n = token_length;
	for ( size_t i = 0; i < n; i++ )
	{
		long double result;
		if ( Slice_to_ld(tokens[i], &result) )
		{
			push_Stack(stack, result);
		}
		else if ( Slice_str_cmp(tokens[i], "+") )
		{
			perform_operation(ADD, stack, &result);
			push_Stack(stack, result);
			printf("%.15Lg\n", result);
		}
		else if ( Slice_str_cmp(tokens[i], "-") )
		{
			perform_operation(SUBTRACT, stack, &result);
			push_Stack(stack, result);
			printf("%.15Lg\n", result);
		}
		else if ( Slice_str_cmp(tokens[i], "*") )
		{
			perform_operation(MULTIPLY, stack, &result);
			push_Stack(stack, result);
			printf("%.15Lg\n", result);
		}
		else if ( Slice_str_cmp(tokens[i], "/") )
		{
			perform_operation(DIVIDE, stack, &result);
			push_Stack(stack, result);
			printf("%.15Lg\n", result);
		}
		else if ( Slice_str_cmp(tokens[i], "%") )
		{
			perform_operation(MODULO, stack, &result);
			push_Stack(stack, result);
			printf("%.15Lg\n", result);
		}

		// 		else if ( c == '+' || c == '-' || c == '/' || c == '*' || c == '%' )
		// 		{
		// 			if ( stack->stack_size < 2 )
		// 			{
		// 				return create_Result_err("Not enough arguments in stack to perform operation", 1, i);
		// 			}
		// 			long double operand1 = pop_Stack(stack);
		// 			long double operand2 = pop_Stack(stack);
		// 			switch ( c )
		// 			{
		// 				case '+':
		// 					push_Stack(stack, operand2 + operand1);
		// 					break;
		// 				case '-':
		// 					push_Stack(stack, operand2 - operand1);
		// 					break;
		// 				case '*':
		// 					push_Stack(stack, operand2 * operand1);
		// 					break;
		// 				case '/':
		// 					if ( operand1 == 0.0l )
		// 					{
		// 						push_Stack(stack, operand2);
		// 						push_Stack(stack, operand1);
		// 						return create_Result_err("Attemped to divide by zero, invalid operation\n", 1, i);
		// 					}
		// 					push_Stack(stack, operand2 / operand1);
		// 					break;
		// 				case '%':
		// 					if ( operand1 == 0.0l )
		// 					{
		// 						push_Stack(stack, operand2);
		// 						push_Stack(stack, operand1);
		// 						return create_Result_err("Attemped to Modulo by zero, invalid operation\n", 1, i);
		// 					}
		// 					push_Stack(stack, fmodl(operand2, operand1));
		// 					break;
		// 			}
		// 		}
		// 		else
		// 		{
		// #define TEMP_SIZE 5
		// 			char temp[TEMP_SIZE] = { 0 };
		// 			int temp_len = 0;
		// 			size_t original_index = i;
		// 			while ( i < n && temp_len < TEMP_SIZE && isalpha(input.string[i]) )
		// 			{
		// 				temp[temp_len] = input.string[i];
		// 				i++;
		// 				temp_len++;
		// 			}
		// #undef TEMP_SIZE
		// 			if ( strcmp(temp, "d") == 0 )
		// 			{
		// 				if ( stack->stack_size > 0 )
		// 				{
		// 					push_Stack(stack, stack->nums[stack->stack_size - 1]);
		// 				}
		// 				else
		// 				{
		// 					return create_Result_err("No items on the stack to duplicate", temp_len, original_index);
		// 				}
		// 			}
		// 			if ( strcmp(temp, "t") == 0 )
		// 			{
		// 				print_stack_top(*stack);
		// 			}
		// 			else if ( strcmp(temp, "o") == 0 )
		// 			{
		// 				if ( stack->stack_size == 0 )
		// 				{
		// 					return create_Result_err("No items to on the stack to be popped", temp_len, original_index);
		// 				}
		// 				long double popped = pop_Stack(stack);
		// 				printf("%Lf\n", popped);
		// 			}
		// 			else if ( strcmp(temp, "c") == 0 )
		// 			{
		// 				stack->stack_size = 0;
		// 			}
		// 			else if ( strcmp(temp, "s") == 0 )
		// 			{
		// 				if ( stack->stack_size >= 2 )
		// 				{
		// 					long double temp = stack->nums[stack->stack_size - 1];
		// 					stack->nums[stack->stack_size - 1] = stack->nums[stack->stack_size - 2];
		// 					stack->nums[stack->stack_size - 2] = temp;
		// 				}
		// 				else
		// 				{
		// 					return create_Result_err("Not enough items in the stack to swap top two elements", temp_len,
		// original_index);
		// 				}
		// 			}
		// 			else if ( strcmp(temp, "p") == 0 )
		// 			{
		// 				print_Stack(*stack);
		// 			}
		// 			else if ( strcmp(temp, "pi") == 0 )
		// 			{
		// 				push_Stack(stack, M_PI);
		// 			}
		// 			else if ( strcmp(temp, "tau") == 0 )
		// 			{
		// 				push_Stack(stack, 2.0L * M_PI);
		// 			}
		// 			else if ( strcmp(temp, "sin") == 0 )
		// 			{
		// 				if ( stack->stack_size == 0 )
		// 				{
		// 					return create_Result_err("Not enough items to do operation", temp_len, original_index);
		// 				}
		// 				long double degrees = pop_Stack(stack);
		// 				if ( !use_radians )
		// 				{
		// 					degrees = deg_to_rad(degrees);
		// 				}
		// 				push_Stack(stack, sinl(degrees));
		// 			}
		// 			else if ( strcmp(temp, "cos") == 0 )
		// 			{
		// 				if ( stack->stack_size == 0 )
		// 				{
		// 					return create_Result_err("Not enough items to do operation", temp_len, original_index);
		// 				}
		// 				long double degrees = pop_Stack(stack);
		// 				if ( !use_radians )
		// 				{
		// 					degrees = deg_to_rad(degrees);
		// 				}
		// 				push_Stack(stack, cosl(degrees));
		// 			}
		// 			else if ( strcmp(temp, "tan") == 0 )
		// 			{
		// 				if ( stack->stack_size == 0 )
		// 				{
		// 					return create_Result_err("Not enough items to do operation", temp_len, original_index);
		// 				}
		// 				long double degrees = pop_Stack(stack);
		// 				if ( !use_radians )
		// 				{
		// 					degrees = deg_to_rad(degrees);
		// 				}
		// 				else
		// 				{
		// 					push_Stack(stack, tanl(degrees));
		// 				}
		// 			}
		// 			else if ( strcmp(temp, "sqrt") == 0 )
		// 			{
		// 				if ( stack->stack_size == 0 )
		// 				{
		// 					return create_Result_err("No items on stack to perform operation", temp_len, original_index);
		// 				}
		// 				long double popped = pop_Stack(stack);
		// 				if ( popped < 0 )
		// 				{
		// 					return create_Result_err("Attempted to take square root of negative number", temp_len,
		// original_index); 					push_Stack(stack, popped);
		// 				}
		// 				push_Stack(stack, sqrtl(popped));
		// 			}
		// 			else if ( temp_len == 2 && temp[0] == '=' )
		// 			{
		// 			}
		// 			else
		// 			{
		// 				return create_Result_err("Found an illegal token", temp_len, original_index);
		// 			}
		// 		}
		// 	}
		// 	if ( stack->stack_size == 0 )
		// 	{
		// 		return create_Result(0.0L);
		// 	}
		// 	else
		// 	{
		// 		return create_Result(stack->nums[stack->stack_size - 1]);
		// 	}
	}
	return create_Result(0.0L);
}

bool perform_operation(Operation op, Stack* stack, long double* result)
{
	assert(stack != NULL);
	if ( stack->stack_size < 2 )
	{
		if ( result != NULL )
		{
			*result = INFINITY;
		}
		return false;
	}
	long double operand1 = pop_Stack(stack);
	long double operand2 = pop_Stack(stack);
	long double calc_result;
	switch ( op )
	{
		case ADD:
			{
				calc_result = operand2 + operand1;
			};
			break;
		case SUBTRACT:
			{
				calc_result = operand2 - operand1;
			};
			break;
		case MULTIPLY:
			{
				calc_result = operand2 * operand1;
			};
			break;
		case DIVIDE:
			{
				if ( operand2 == 0.0L )
				{
					if ( result != NULL )
						*result = 0.0L;
					return false;
				}
				calc_result = operand2 / operand1;
			};
			break;
		case MODULO:
			{
				if ( operand2 == 0.0L )
				{
					if ( result != NULL )
						*result = 0.0L;
					return false;
				}
				calc_result = fmod(operand2, operand1);
			};
			break;
	};
	if ( result != NULL )
	{
		*result = calc_result;
	}
	return true;
}

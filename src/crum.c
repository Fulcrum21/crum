#include "crum.h"

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern bool use_radians;

typedef enum { ADD, SUBTRACT, MULTIPLY, DIVIDE, MODULO, SIN, COS, TAN } Operation;

// Performs the operation op on the stack, and stores the result of the calculation
// in the pointer result
// this returns true if the calculation was successful, and false otherwise
// if false is returned, check the value inside the result pointer for the error
// result = INFINITY: there are less than two items in the stack
// result = 0.0: the denominator in the division and modulo operations is zero
Result perform_operation(Operation op, Stack* stack);

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

Result evaluate_tokens(Stack* stack, Slice tokens[], size_t token_length)
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
			Result result = perform_operation(ADD, stack);
			if ( !result.is_err )
				push_Stack(stack, result.result);
			else
			{
				result.error.illegal_token = tokens[i];
				return result;
			}
		}
		else if ( Slice_str_cmp(tokens[i], "-") )
		{
			Result result = perform_operation(SUBTRACT, stack);
			if ( !result.is_err )
				push_Stack(stack, result.result);
			else
			{
				result.error.illegal_token = tokens[i];
				return result;
			}
		}
		else if ( Slice_str_cmp(tokens[i], "*") )
		{
			Result result = perform_operation(MULTIPLY, stack);
			if ( !result.is_err )
				push_Stack(stack, result.result);
			else
			{
				result.error.illegal_token = tokens[i];
				return result;
			}
		}
		else if ( Slice_str_cmp(tokens[i], "/") )
		{
			Result result = perform_operation(DIVIDE, stack);
			if ( !result.is_err )
				push_Stack(stack, result.result);
			else
			{
				result.error.illegal_token = tokens[i];
				return result;
			}
		}
		else if ( Slice_str_cmp(tokens[i], "%") )
		{
			Result result = perform_operation(MODULO, stack);
			if ( !result.is_err )
				push_Stack(stack, result.result);
			else
			{
				result.error.illegal_token = tokens[i];
				return result;
			}
		}
		else if ( Slice_str_cmp(tokens[i], "p") )
		{
			print_Stack(*stack);
		}
		else if ( Slice_str_cmp(tokens[i], "d") )
		{
			if ( stack->stack_size > 0 )
			{
				push_Stack(stack, stack->nums[stack->stack_size]);
			}
			else
			{
				return create_Result_err("No items in stack to duplicate", tokens[i]);
			}
		}
		else if ( Slice_str_cmp(tokens[i], "o") )
		{
			if ( stack->stack_size > 0 )
			{
				printf("%.11Lg\n", pop_Stack(stack));
			}
			else
			{
				return create_Result_err("No items in stack to pop", tokens[i]);
			}
		}
		else if ( Slice_str_cmp(tokens[i], "pi") )
		{
			push_Stack(stack, M_PI);
		}
		else if ( Slice_str_cmp(tokens[i], "tau") )
		{
			push_Stack(stack, M_PI * 2.0L);
		}
		else if ( Slice_str_cmp(tokens[i], "sin") )
		{
			Result result = perform_operation(SIN, stack);
			if ( result.is_err )
				return result;
			else
			{
				push_Stack(stack, result.result);
			}
		}
		else if ( Slice_str_cmp(tokens[i], "cos") )
		{
			Result result = perform_operation(COS, stack);
			if ( result.is_err )
				return result;
			else
			{
				push_Stack(stack, result.result);
			}
		}
		else if ( Slice_str_cmp(tokens[i], "tan") )
		{
			Result result = perform_operation(TAN, stack);
			if ( result.is_err )
				return result;
			else
			{
				push_Stack(stack, result.result);
			}
		}
		else
		{
			return create_Result_err("Illegal token", tokens[i]);
		}
	}
	return create_Result(0.0L);
}

Result perform_operation(Operation op, Stack* stack)
{
	assert(stack != NULL);
	long double calc_result = 0.0L;
	if ( op == SIN || op == TAN || op == COS )
	{
		if ( stack->stack_size < 1 )
		{
			return create_Result_err("Requires atleast one argument on the stack", Slice_NULL);
		}
		long double trig_arg = pop_Stack(stack);
		if ( !use_radians )
		{
			trig_arg = deg_to_rad(trig_arg);
		}
		switch ( op )
		{
			case SIN:
				calc_result = sinl(trig_arg);
				break;
			case COS:
				calc_result = cosl(trig_arg);
				break;
			case TAN:
				calc_result = tanl(trig_arg);
				break;
			default:
				break;
		}
	}
	else
	{

		if ( stack->stack_size < 2 )
		{
			return create_Result_err("requires atleast two arguments on the stack", Slice_NULL);
		}
		long double operand1 = pop_Stack(stack);
		long double operand2 = pop_Stack(stack);
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
					if ( operand1 == 0.0L )
					{
						push_Stack(stack, operand2);
						push_Stack(stack, operand1);
						return create_Result_err("Denominator of / is 0", Slice_NULL);
					}
					calc_result = operand2 / operand1;
				};
				break;
			case MODULO:
				{
					if ( operand1 == 0.0L )
					{
						push_Stack(stack, operand2);
						push_Stack(stack, operand1);
						return create_Result_err("Denominator of % is 0", Slice_NULL);
					}
					calc_result = fmod(operand2, operand1);
				};
				break;
			default:
				break;
		};
	}
	return create_Result(calc_result);
}

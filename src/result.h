#ifndef RESULT_H_
#define RESULT_H_
#include "slice.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
typedef struct
{
	char* err_str;
	Slice illegal_token;
} Error;
typedef struct
{
	union
	{
		long double result;
		Error error;
	};
	bool is_err;
} Result;

Result create_Result(long double result);
Result create_Result_err(char* error, Slice slice);
#endif // RESULT_H_

#ifdef RESULT_IMPL
Result create_Result(long double result)
{
	return (Result){
		.is_err = false,
		.result = result,
	};
}
Result create_Result_err(char* error, Slice slice)
{
	return (Result){
		.is_err = true, .error = (Error){.err_str = error, .illegal_token = slice}
	};
}
#endif

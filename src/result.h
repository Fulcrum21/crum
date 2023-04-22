#ifndef RESULT_H_
#define RESULT_H_
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
typedef struct
{
	char* err_str;
	size_t index;
	uint8_t token_length;

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
Result create_Result_err(char* error, uint8_t token_length, size_t index);
#endif // RESULT_H_

#ifdef RESULT_IMPL
Result create_Result(long double result)
{
	return (Result){
		.is_err = false,
		.result = result,
	};
}
Result create_Result_err(char* error, uint8_t token_length, size_t index)
{
	return (Result){
		.is_err = true, .error = (Error){.err_str = error, .index = index, .token_length = token_length}
	};
}
#endif

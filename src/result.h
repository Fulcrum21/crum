#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#ifndef RESULT_H_
#define RESULT_H_
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

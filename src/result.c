#include "result.h"

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

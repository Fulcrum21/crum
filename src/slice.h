#ifndef SLICE_H_
#define SLICE_H_
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#define Slice_str_cmp(slice, str) (((slice).size == (strlen(str))) && (strncmp((slice).string, (str), (slice).size) == 0))
#define Slice_cmp(slice1, slice2) \
 (((slice1).size == (slice2).size) && (strncmp((slice1).string, (slice2).string, (slice1).size) == 0))
typedef struct
{
	const char* string;
	size_t size;
} Slice;

Slice Slice_from_cstr(const char* cstr);
Slice Slice_from_parts(const char* string, size_t size);
Slice Slice_trim_left(Slice slice);
Slice Slice_trim_right(Slice slice);
Slice Slice_trim(Slice slice);
bool Slice_tok(Slice* slice, Slice* result, char delim);
bool Slice_to_ld(Slice slice, long double* result);

#endif // SLICE_H_

#ifdef SLICE_IMPL
#include <assert.h>
#include <ctype.h>
Slice Slice_from_parts(const char* string, size_t size)
{
	assert(string != NULL);
	return (Slice){
		.string = string,
		.size = size,
	};
}
Slice Slice_from_cstr(const char* cstr)
{
	assert(cstr != NULL);
	return (Slice){
		.string = cstr,
		.size = strlen(cstr),
	};
}

Slice Slice_trim_left(Slice slice)
{
	size_t i = 0;
	for ( ; i < slice.size && isspace(slice.string[i]); i++ )
	{
	}
	return (Slice){
		.string = slice.string + i,
		.size = slice.size - i,
	};
}
Slice Slice_trim_right(Slice slice)
{
	size_t i = 0;
	for ( ; i < slice.size && isspace(slice.string[slice.size - 1 - i]); i++ )
	{
	}
	return (Slice){
		.string = slice.string,
		.size = slice.size - i,
	};
}
Slice Slice_trim(Slice slice)
{
	return Slice_trim_right(Slice_trim_left(slice));
}

bool Slice_to_ld(Slice slice, long double* result)
{
	char buffer[slice.size + 1];
	buffer[slice.size] = 0;
	memcpy(buffer, slice.string, slice.size);
	char* end_of_numstr;
	long double conversion = strtold(buffer, &end_of_numstr);
	if ( (end_of_numstr - buffer) != slice.size )
	{
		return false;
	}
	else
	{
		if ( result != NULL )
		{
			*result = conversion;
		}
	}
	return true;
}
bool Slice_tok(Slice* slice, Slice* result, char delim)
{
	assert(slice != NULL);
	size_t i = 0;
	for ( ; i < slice->size && slice->string[i] == delim; i++ )
	{
	}
	if ( i >= slice->size )
	{
		return false;
	}
	size_t original_i = i;
	for ( ; i < slice->size && slice->string[i] != delim; i++ )
	{
	}
	if ( result != NULL )
	{
		*result = Slice_from_parts(slice->string + original_i, i - original_i);
	}
	if ( i < slice->size )
	{
		slice->string += (i + 1);
		slice->size -= (i + 1);
	}
	else
	{
		slice->string += i;
		slice->size -= i;
	}
	return true;
}
#endif // SLICE_IMPL

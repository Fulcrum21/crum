#include "slice.h"

#include <assert.h>
#include <ctype.h>
#include <string.h>

Slice init_Slice_from_parts(char* string, size_t size)
{
	assert(string != NULL);
	return (Slice){
		.string = string,
		.size = size,
	};
}
Slice init_Slice_from_cstr(const char* cstr)
{
	assert(cstr != NULL);
	return (Slice){
		.string = cstr,
		.size = strlen(cstr),
	};
}

Slice trim_left(Slice slice)
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
Slice trim_right(Slice slice)
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
Slice trim(Slice slice)
{
	return trim_right(trim_left(slice));
}
// bool Slice_cmp(Slice slice1, Slice slice2)
// {
// 	return ((slice1.size == slice2.size) && (strncmp(slice1.string, slice2.string, slice1.size) == 0));
// }

#ifndef SLICE_H_
#define SLICE_H_
#include <stdbool.h>
#include <stddef.h>
typedef struct
{
	const char* string;
	size_t size;
} Slice;
Slice init_Slice_from_cstr(const char* cstr);
Slice init_Slice_from_parts(char* string, size_t size);
Slice trim_left(Slice slice);
Slice trim_right(Slice slice);
Slice trim(Slice slice);
bool Slice_cmp(Slice slice1, Slice slice2);
#endif // SLICE_H_

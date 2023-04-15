#define Slice_cmp(slice1, slice2) \
 (((slice1).size == (slice2).size) && (strncmp((slice1).string, (slice2).string, (slice1).size) == 0))
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
#endif // SLICE_H_

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

#define Slice_NULL ((Slice){ .string = NULL, .size = 0 })
#define Slice_fmt_arg(Slice) (int) (Slice.size), (Slice.string)

Slice Slice_from_cstr(const char* cstr);
Slice Slice_from_parts(const char* string, size_t size);
Slice Slice_trim_left(Slice slice);
Slice Slice_trim_right(Slice slice);
Slice Slice_trim(Slice slice);
bool Slice_tok(Slice* slice, Slice* result, char delim);
bool Slice_to_ld(Slice slice, long double* result);

#endif // SLICE_H_

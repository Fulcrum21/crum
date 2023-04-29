#include "result.h"
#include "slice.h"
#include "stack.h"
#ifndef CRUM_H_
#define CRUM_H_

void print_stack_top(Stack stack);
Result evaluate_tokens(Stack* stack, Slice tokens[], size_t token_length);

#endif // CRUM_H_

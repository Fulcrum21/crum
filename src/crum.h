#include "slice.h"
#include "stack.h"
#ifndef CRUM_H_
#define CRUM_H_

void print_stack_top(Stack stack);
void evaluate_string(Stack* stack_ptr, Slice input);

#endif // CRUM_H_

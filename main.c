#include "crum.h"
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	// const char* input = "3 pi * 5 pi * 2 + 3 / / p";
	const char* input = "p";
	Stack stack = init_Stack();
	evaluate_string(&stack, input);
	return EXIT_SUCCESS;
}

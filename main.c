#include "crum.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* welcome_msg = "Welcome to CRUM, a Reverse Polish Notation calculator.\nType 'help' for help\n";
const char* help_msg =
    "Basic arithmetic: + - * / %\n\ncommands:\np - Prints the top of the stack\n\nsupported functions:\nsin\n\n\
Make sure to put a space between every part of the expression, even if an expression with no spaces may be valid, most expressions will be ambigous to the parser";

int main(int argc, char* argv[])
{
	Stack stack = { 0 };
	fputs(welcome_msg, stdout);
	fputs(">>> ", stdout);
	while ( 1 )
	{
		char buffer[1024] = { 0 };
		if ( !fgets(buffer, 1024, stdin) )
		{
			if ( ferror(stdout) )
			{
				puts("Error whilst reading input\n");
			}
			break;
		}
		Slice input_slice = trim(init_Slice_from_cstr(buffer));
		if ( Slice_cmp(input_slice, init_Slice_from_cstr("help")) )
		{
			puts(help_msg);
		}
		else if ( Slice_cmp(input_slice, init_Slice_from_cstr("quit")) )
		{
			puts("Thank you for using CRUM");
			break;
		}
		else
		{
			evaluate_string(&stack, input_slice);
		}
		fputs(">>> ", stdout);
	}
	return EXIT_SUCCESS;
}

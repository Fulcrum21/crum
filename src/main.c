// TODO: add more commands
// TODO: Variables
// TODO: better error handling
// TODO: bignum support
#include "crum.h"
#include <libgen.h>
#include <stdio.h>
#include <string.h>

extern bool use_radians;
bool use_radians = false;

const char* welcome_msg =
    "Welcome to CRUM, a Reverse Polish Notation calculator.\nType 'help' for help, 'quit' 'exit' or 'q' to exit\n";
const char* help_msg =
    "Basic arithmetic: + - * / %\n\nCommands:\n\tt - Prints the top of the stack\n\to (letter) - Pops the top element in the stack and prints it\n\tc - Clears the stack\n\ts - Swaps the top two elements in the stack\n\td - Duplicate the top element of the stack\n\nFunctions:\n\tsin\n\tcos\n\ttan\n\nConstants:\n\tpi\n\ttau (2*pi)\n\nMake sure to put a space between every part of the expression\n";

int main(int argc, char* argv[])
{
	for ( int i = 1; i < argc; i++ )
	{
		if ( strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 )
		{
			printf("Usage: %s [options]\n", basename(argv[0]));
			puts("Options:\n");
			puts("  -h, --help\t\tShows this help message");
			puts("  --radians\t\tUses radians instead of degrees");
			return 0;
		}
		else if ( strcmp(argv[i], "--radians") == 0 )
		{
			use_radians = true;
		}
		else
		{
			fprintf(stderr, "Invalid option: %s\n", argv[i]);
			return 1;
		}
	}

	Slice help_slice = init_Slice_from_cstr("help");
	Slice quit_slice = init_Slice_from_cstr("quit");
	Slice q_slice = init_Slice_from_cstr("q");
	Slice exit_slice = init_Slice_from_cstr("exit");
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
		if ( Slice_cmp(input_slice, help_slice) )
		{
			puts(help_msg);
		}
		else if ( Slice_cmp(input_slice, quit_slice) || Slice_cmp(input_slice, q_slice) || Slice_cmp(input_slice, exit_slice) )
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
	return 0;
}
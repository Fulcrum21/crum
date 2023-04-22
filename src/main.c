// TODO: Variables
// TODO: better error handling
// TODO: bignum support
#define RESULT_IMPL
#define SLICE_IMPL
#include "crum.h"
#include <libgen.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#define BUFFERSIZE 1024
#define TOKENSIZE BUFFERSIZE / 2

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

	Slice help_slice = Slice_from_cstr("help");
	Slice quit_slice = Slice_from_cstr("quit");
	Slice q_slice = Slice_from_cstr("q");
	Slice exit_slice = Slice_from_cstr("exit");
	Stack stack = { 0 };
	fputs(welcome_msg, stdout);
	fputs(">>> ", stdout);
	while ( 1 )
	{
		size_t tokensize = 0;
		Slice tokens[TOKENSIZE] = { 0 };
		char buffer[BUFFERSIZE] = { 0 };
		if ( !fgets(buffer, BUFFERSIZE, stdin) )
		{
			if ( ferror(stdout) )
			{
				puts("Error whilst reading input\n");
			}
			break;
		}
		Slice input_slice = Slice_trim(Slice_from_cstr(buffer));
		while ( 1 )
		{
			Slice result;
			if ( !Slice_tok(&input_slice, &result, ' ') )
			{
				break;
			}
			tokens[tokensize++] = result;
		}
		evaluate_string(&stack, tokens, tokensize);
		// if ( Slice_cmp(input_slice, help_slice) )
		// {
		// 	puts(help_msg);
		// }
		// else if ( Slice_cmp(input_slice, quit_slice) || Slice_cmp(input_slice, q_slice) || Slice_cmp(input_slice, exit_slice) )
		// {
		// 	puts("Thank you for using CRUM");
		// 	break;
		// }
		// else
		// {
		// 	Result result = evaluate_string(&stack, input_slice);
		// 	if ( result.is_err )
		// 	{
		// 		printf("Error: %s\nToken: %.*s\n", result.error.err_str, result.error.token_length,
		// 		    input_slice.string + result.error.index);
		// 	}
		// }
		fputs(">>> ", stdout);
	}
	return 0;
}

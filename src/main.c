#include <stdio.h>

#include "program.h"

int main()
{
	FILE* file = fopen("examples/hello-world.bf", "r");

	program* program = create_program_from_file(file);
	execute_program(program);

	return 0;
}

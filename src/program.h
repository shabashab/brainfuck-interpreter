#include <stdio.h>

#include "execution-stack.h"
#include "data-storage.h"
#include "token.h"

#ifndef PROGRAM_H
#define PROGRAM_H

typedef struct program_s {
	execution_stack* stack;
	data_storage* storage;

	token* tokens;
	size_t tokens_count;
} program;

program* create_program_from_file(FILE* file);
void execute_program(program* program);

#endif

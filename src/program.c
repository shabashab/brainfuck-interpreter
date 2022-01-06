#include <stdio.h>
#include <string.h>

#include "program.h"

#include "execution-frame.h"
#include "execution-stack.h"
#include "data-storage.h"

#define BUFFER_SIZE 256

typedef struct file_reading_result_s {
	char* data;
	size_t data_len;
} file_reading_result;

static file_reading_result read_file_contents(FILE* file)
{
	file_reading_result result;
	result.data = NULL;

	char buffer[BUFFER_SIZE];
	size_t count;

	while((count = fread(buffer, sizeof(char), BUFFER_SIZE, file))) {
		result.data_len += count;
		result.data = realloc(result.data, result.data_len);
		memcpy(result.data + (result.data_len - count - 1), buffer, count);
	}
	
	return result;
}

static token parse_char(char ch)
{
	switch(ch) {
		case TOKEN_PLUS:
			return TOKEN_PLUS;
		case TOKEN_MINUS:
			return TOKEN_MINUS;
		case TOKEN_INPUT:
			return TOKEN_INPUT;
		case TOKEN_INC_DATA:
			return TOKEN_INC_DATA;
		case TOKEN_DEC_DATA:
			return TOKEN_DEC_DATA;
		case TOKEN_PRINT:
			return TOKEN_PRINT;
		case TOKEN_WHILE_START:
			return TOKEN_WHILE_START;
		case TOKEN_WHILE_END:
			return TOKEN_WHILE_END;
		default:
			return TOKEN_OTHER;
	}
}

program* create_program_from_file(FILE* file)
{
	program* result = malloc(sizeof(program));

	result->stack = es_create();
	result->storage = ds_create();

	file_reading_result reading_result = read_file_contents(file);

	size_t tokens_count = 0;
	token* tokens = malloc(sizeof(token) * reading_result.data_len);

	for(int i = 0; i < reading_result.data_len; i++) {
		token new_token = parse_char(reading_result.data[i]);

		if(new_token == TOKEN_OTHER)
			continue;

		tokens[i] = new_token;
		tokens_count++;
	}

	tokens = realloc(tokens, tokens_count);

	result->tokens = tokens;
	result->tokens_count = tokens_count;

	execution_frame default_frame;

	default_frame.start_token = tokens;

	es_push(result->stack, default_frame);

	return result;
}

void execute_top_frame(program* program) {
	execution_frame* frame = es_peek(program->stack);
	token* cur_token = frame->start_token;

	while(cur_token <= (program->tokens + (program->tokens_count - 1))) {
		switch(*cur_token) {
			case TOKEN_PLUS:
				ds_increment(program->storage);
				break;
			case TOKEN_MINUS:
				ds_decrement(program->storage);
				break;
			case TOKEN_INC_DATA:
				ds_move_right(program->storage);
				break;
			case TOKEN_DEC_DATA:
				ds_move_left(program->storage);
				break;
			case TOKEN_PRINT:
				putc(ds_get(program->storage), stdout);
				break;
			case TOKEN_INPUT:
				ds_set(program->storage, getchar());
				break;
			case TOKEN_WHILE_START:
				break;
			case TOKEN_WHILE_END:
				break;
			case TOKEN_OTHER:
			default:
				break;
		}

		if(*cur_token == TOKEN_WHILE_START) {
			execution_frame frame;			

			frame.start_token = cur_token + 1;

			es_push(program->stack, frame);
			execute_top_frame(program);
		}

		if(*cur_token == TOKEN_WHILE_END) {
			if(ds_get(program->storage)) {
				cur_token = frame->start_token;
				continue;
			}

			break;
		}

		cur_token++;
	}

	es_pop(program->stack);
}

void execute_program(program* program) {
	execute_top_frame(program);
}

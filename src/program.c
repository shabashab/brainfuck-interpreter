#include "program.h"

#define BUFFER_SIZE 256

typedef struct file_reading_result_s {
	char* data;
	size_t data_len;
} file_reading_result;

static file_reading_result read_file_contents(FILE* file)
{
	file_reading_result result;

	result.data = malloc(0);

	char buffer[BUFFER_SIZE];
	size_t count;

	while((count = fread(&buffer, sizeof(char),	BUFFER_SIZE, file))) {
		result.data_len += count;
		result.data = realloc(result.data, result.data_len);
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

	execution_frame default_frame;

	default_frame.start_token = tokens;
	default_frame.end_token = tokens + tokens_count - 1;

	es_push(result->stack, default_frame);

	return result;
}

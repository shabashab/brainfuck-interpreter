#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF_SIZE 1024

typedef struct LLNode_s LLNode;

struct LLNode_s {
	int8_t data;
	LLNode* next;
	LLNode* prev;
};

LLNode* cur_node;

LLNode* create_list()
{
	LLNode* node = malloc(sizeof(LLNode));
	node->prev = NULL;
	node->next = NULL;
	node->data = 0;
	return node;
}

void process_character(char c)
{
	switch(c) {
		case '+':
			cur_node->data++;
			break;
		case '-':
			cur_node->data--;
			break;
		case '.':
			fputc((char)cur_node->data, stdout);
			break;
		default:
			break;
	}
}

int main()
{
	//Init data array
	cur_node = create_list();

	const char* filename = "examples/print-1.bf";

	FILE* input_file = fopen(filename, "r");

	char value;
	while((value = fgetc(input_file)) != EOF) {
		process_character(value);
	}

	fclose(input_file);

	return 0;
}

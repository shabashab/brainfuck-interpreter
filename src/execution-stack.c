#include "execution-frame.h"
#include "execution-stack.h"

typedef struct execution_stack_s execution_stack;
typedef struct es_node_s es_node;


struct execution_stack_s {
	es_node* top_node;
};

struct es_node_s {
	execution_frame frame;
	es_node* bottom_node;
};

es_node* create_node(es_node* bottom, execution_frame data)
{
	es_node* node = malloc(sizeof(es_node));

	node->bottom_node = bottom;
	node->frame = data;

	return node;
}

execution_stack* es_create()
{
	execution_stack* stack = malloc(sizeof(execution_stack));
	stack->top_node = NULL;

	return stack;
}

void es_pop(execution_stack* stack)
{
	es_node* prev_node = stack->top_node;
	stack->top_node = prev_node->bottom_node;
	free(prev_node);
}

execution_frame* es_peek(execution_stack* stack)
{
	return &(stack->top_node->frame);
}

void es_push(execution_stack* stack, execution_frame frame)
{
	es_node* new_node = create_node(stack->top_node, frame);
	stack->top_node = new_node;
}

void es_free(execution_stack* stack)
{
	//Freeing all the data nodes
	es_node* cur_node = stack->top_node;
	es_node* next_node;

	while(cur_node) {
		next_node = cur_node->bottom_node;
		free(cur_node);
		cur_node = next_node;
	}

	free(stack);
}

#include "execution-frame.h"

typedef struct execution_stack_s execution_stack;

execution_stack* es_create();

void es_pop(execution_stack* stack);
execution_frame* es_peek(execution_stack* stack);
void es_push(execution_stack* stack, execution_frame frame);

void es_free(execution_stack* stack);

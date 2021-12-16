#include <stdlib.h>

#include "data-storage.h"

typedef struct ds_node_s ds_node;

struct ds_node_s {
	int8_t value;
	ds_node* prev;
	ds_node* next;
};

struct data_storage_s {
	ds_node* first_node;
	ds_node* cur_node;
};

ds_node* create_ds_node(ds_node* prev) {
	ds_node* node = malloc(sizeof(ds_node));

	node->value = 0;
	node->next = NULL;
	
	node->prev = prev;
	if(prev)
		prev->next = node;

	return node;
}

data_storage* ds_create()
{
	data_storage* storage = malloc(sizeof(data_storage));

	storage->cur_node = create_ds_node(NULL);

	return storage;
}

int8_t* ds_move_right(data_storage* storage)
{
	if(storage->cur_node->next == NULL) {
		ds_node* new_node = create_ds_node(storage->cur_node);
		storage->cur_node = new_node;	
	} else {
		storage->cur_node = storage->cur_node->next;
	}

	return &(storage->cur_node->value);
}

int8_t* ds_move_left(data_storage* storage)
{
	if(storage->cur_node->prev == NULL)
		return NULL;

	storage->cur_node = storage->cur_node->prev;
	return &(storage->cur_node->value);
}

int8_t* ds_increment(data_storage* storage)
{
	storage->cur_node->value++;
	return &(storage->cur_node->value);
}

int8_t* ds_decrement(data_storage* storage)
{
	storage->cur_node->value--;
	return &(storage->cur_node->value);
}

int8_t* ds_set(data_storage* storage, int8_t data)
{
	storage->cur_node->value = data;
	return &(storage->cur_node->value);
}

int8_t ds_get(data_storage* storage)
{
	return storage->cur_node->value;
}

void ds_free(data_storage* storage)
{
	//Freeing all the data nodes
	ds_node* cur_node = storage->first_node;
	ds_node* next_node;

	while(cur_node) {
		next_node = cur_node->next;
		free(cur_node);
		cur_node = next_node;
	}

	//Freeing the storage itself
	free(storage);
}

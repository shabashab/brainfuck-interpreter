#include <stdint.h>

#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

typedef struct data_storage_s data_storage;

data_storage* ds_create();

int8_t* ds_move_right(data_storage* storage);
int8_t* ds_move_left(data_storage* storage);
int8_t* ds_increment(data_storage* storage);
int8_t* ds_decrement(data_storage* storage);
int8_t* ds_set(data_storage* storage, int8_t data);
int8_t	ds_get(data_storage* storage);

void ds_free(data_storage* storage);

#endif

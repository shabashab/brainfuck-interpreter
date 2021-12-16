#include <stdlib.h>

#include "token.h"

#ifndef EXEUCTION_FRAME_H
#define EXEUCTION_FRAME_H

typedef struct execution_frame_s execution_frame;

struct execution_frame_s {
	token* start_token;	
	token* end_token;
};

#endif

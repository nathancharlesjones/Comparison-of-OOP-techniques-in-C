#ifndef RUBBER_H
#define RUBBER_H

#define MAX_NUM_RUBBER_OBJS 10

#include "duck.h"

typedef enum {SMALL, MEDIUM, LARGE} duck_size;

Duck rubberCreate_dynamic( char * name, duck_size size );
Duck rubberCreate_static( char * name, duck_size size );

#endif // RUBBER_H
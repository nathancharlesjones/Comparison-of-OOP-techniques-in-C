#ifndef MALLARD_H
#define MALLARD_H

#define MAX_NUM_MALLARD_OBJS 10

#include "duck.h"

typedef enum {RED, BROWN, WHITE} featherColor;

Duck mallardCreate_dynamic( char * name, featherColor color );
Duck mallardCreate_static( char * name, featherColor color );

#endif // MALLARD_H
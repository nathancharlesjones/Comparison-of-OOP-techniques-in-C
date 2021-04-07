#ifndef RED_MALLARD_H
#define RED_MALLARD_H

#include "mallard.h"

#define MAX_NUM_RED_MALLARD_OBJS 10

void * redMallardCreate_dynamic( char * name, featherColor color );
void * redMallardCreate_static( char * name, featherColor color );

#endif // RED_MALLARD_H
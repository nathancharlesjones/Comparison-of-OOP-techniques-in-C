#ifndef DUCK_H
#define DUCK_H

#include "duck.r"

#define MAX_NUM_DUCK_OBJS 10

typedef struct Duck_t * Duck;

extern Duck_Interface duckFromHeapMem;
extern Duck_Interface duckFromStaticMem; 

Duck duckCreate( Duck_Interface newDuckType, char * name, ... );
void duckQuack( Duck thisDuck );
void duckShow( Duck thisDuck );
void duckDestroy( Duck thisDuck );

#endif // DUCK_H
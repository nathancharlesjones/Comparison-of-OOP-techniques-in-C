#ifndef MALLARD_H
#define MALLARD_H

#define MAX_NUM_MALLARD_OBJS 10

#include "duck.h"

typedef enum {RED, BROWN, WHITE} featherColor;

extern const char * colorNames[];

typedef struct Mallard_t * Mallard;

Duck mallardCreate_dynamic( void );
Duck mallardCreate_static( void );
void mallardInit( Duck thisDuck, char * name, featherColor color );
void mallardDeinit( Duck thisDuck );
void mallardDestroy_dynamic( Duck thisDuck );
void mallardDestroy_static( Duck thisDuck );

#endif // MALLARD_H
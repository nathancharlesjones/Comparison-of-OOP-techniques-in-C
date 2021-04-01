#ifndef MALLARD_H
#define MALLARD_H

#include "duck.h"

typedef enum {RED, BROWN, WHITE} featherColor;

extern const char * colorNames[];

typedef struct Mallard_t * Mallard;

Duck mallardCreate( void );
void mallardInit( Duck thisDuck, char * name, featherColor color );

#endif // MALLARD_H
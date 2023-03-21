#ifndef MALLARD_R
#define MALLARD_R

#include "duck.r"
#include "mallard.h"

typedef struct Mallard_Interface_Struct const * Mallard_Interface;

typedef struct Mallard_t
{
    const Duck_t parentDuck;
    featherColor myColor;
} Mallard_t;

typedef struct Mallard_Interface_Struct
{
    Duck_Interface_Struct duckInterface;
    void (*migrate)( Mallard_t * thisMallard );
} Mallard_Interface_Struct;

void mallardInit( Mallard thisMallard, char * name, featherColor color );
void mallardDeinit( Duck thisDuck );

#endif //MALLARD_R
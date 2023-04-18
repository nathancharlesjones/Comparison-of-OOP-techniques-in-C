#ifndef MALLARD_R
#define MALLARD_R

#include "duck.r"
#include "mallard.h"

typedef struct Mallard_Interface_Struct const * Mallard_Interface;

typedef struct Mallard_t
{
    const Duck_t parentDuck;
    featherColor myColor;
} Mallard_t, *Mallard;

typedef struct Mallard_Interface_Struct
{
    Duck_Interface_Struct duckInterface;
    void (*migrate)( void * thisMallard ); // Optional for derived classes; set to "0" or "NULL" to use the default "Mallard" implementation
} Mallard_Interface_Struct;

void mallardInit( Mallard thisMallard, va_list * args );
void mallardDeinit( Mallard thisMallard );

#endif //MALLARD_R
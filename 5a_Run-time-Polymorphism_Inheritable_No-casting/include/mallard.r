#ifndef MALLARD_R
#define MALLARD_R

#include "duck.r"
#include "mallard.h"

typedef struct Mallard_Interface_Struct const * Mallard_Interface;

typedef struct Mallard_t
{
    Duck_t parentDuck;
    featherColor myColor;
} Mallard_t, *Mallard;

typedef struct Mallard_Interface_Struct
{
    Duck_Interface_Struct duckInterface;
    void (*migrate)( void * thisMallard );
} Mallard_Interface_Struct;

#endif //MALLARD_R
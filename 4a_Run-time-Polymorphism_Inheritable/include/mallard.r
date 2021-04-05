#ifndef MALLARD_R
#define MALLARD_R

#include "duck.r"
#include "mallard.h"

typedef struct Mallard_Interface_Struct * Mallard_Interface;

typedef struct Mallard_t
{
    Duck_t parentDuck;
    featherColor myColor;
} Mallard_t;

typedef struct Mallard_Interface_Struct
{
    Duck_Interface_Struct parentInterface;
    void (*migrate)( Mallard_t * thisMallard );
} Mallard_Interface_Struct;

#endif //MALLARD_R
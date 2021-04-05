#ifndef MALLARD_R
#define MALLARD_R

#include "duck.r"

typedef struct Mallard_Interface_Struct * Mallard_Interface;

typedef struct Mallard_t
{
    Duck_t parentDuck;
    featherColor myColor;
} Mallard_t;

typedef struct Mallard_Interface_Struct
{
    Duck_Interface_Struct parentDuck;
    void (*migrate)( void * thisMallard );
} Mallard_Interface_Struct;

extern Mallard_Interface_Struct mallardDef;

#endif //MALLARD_R
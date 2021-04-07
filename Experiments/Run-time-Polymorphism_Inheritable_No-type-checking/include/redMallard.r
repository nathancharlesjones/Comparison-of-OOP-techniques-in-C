#ifndef RED_MALLARD_R
#define RED_MALLARD_R

#include "mallard.r"

typedef struct redMallard_Interface_Struct const * redMallard_Interface;

typedef struct redMallard_t
{
    Mallard_t parentMallard;
} redMallard_t, *redMallard;

typedef struct redMallard_Interface_Struct
{
    Mallard_Interface_Struct mallardInterface;
} redMallard_Interface_Struct;

void redMallardInit( redMallard thisRedMallard, char * name, featherColor color );
void redMallardDeinit( void * thisRedMallard );

#endif // RED_MALLARD_R
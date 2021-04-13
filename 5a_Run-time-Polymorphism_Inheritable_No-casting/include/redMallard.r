#ifndef RED_MALLARD_R
#define RED_MALLARD_R

#include "mallard.r"

typedef struct redMallard_Interface_Struct * redMallard_Interface;

typedef struct redMallard_t
{
    const Mallard_t parentMallard;
} redMallard_t, *redMallard;

typedef struct redMallard_Interface_Struct
{
    Mallard_Interface_Struct mallardInterface;
} redMallard_Interface_Struct;

void redMallardInit( redMallard thisRedMallard, va_list * args );
void redMallardDeinit( redMallard thisRedMallard );

#endif // RED_MALLARD_R
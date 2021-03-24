#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"
#include "mallard.h"
#include "mallard.r"

const char * colorNames[] = {"red", "brown", "white"};

Mallard
mallardCreate( void )
{
    Mallard newMallard = (Mallard)malloc(sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    return newMallard;
}

void
mallardInit( Mallard thisMallard, char * name, featherColor color )
{
    printf("\tInitializing new mallard duck with name: %s\n", name);

    duckInit( &thisMallard->parentDuck, name );

    thisMallard->myColor = color;
}

void
mallardShow( Mallard thisMallard )
{
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", thisMallard->parentDuck.name, colorNames[thisMallard->myColor]);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"
#include "mallard.h"
#include "mallard.r"

const char * colorNames[] = {"red", "brown", "white"};

static void mallardShow( Duck thisDuck );

static Duck_Interface_Struct interface = {
    mallardShow
};

Duck
mallardCreate( void )
{
    Mallard newMallard = (Mallard)malloc(sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    return (Duck)newMallard;
}

void
mallardInit( Duck thisDuck, char * name, featherColor color )
{
    printf("\tInitializing new mallard duck with name: %s\n", name);

    duckInit( thisDuck, name );

    Mallard thisMallard = (Mallard)thisDuck;
    thisMallard->parentDuck.vtable = &interface;
    thisMallard->myColor = color;
}

static void
mallardShow( Duck thisDuck )
{
    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", thisMallard->parentDuck.name, colorNames[thisMallard->myColor]);
}
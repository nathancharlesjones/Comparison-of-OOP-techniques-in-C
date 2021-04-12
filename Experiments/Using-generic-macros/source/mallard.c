#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"
#include "duckInterface.h"
#include "mallard.h"

const char * colorNames[] = {"red", "brown", "white"};

typedef struct Mallard_t
{
    Duck parentDuck;
    featherColor myColor;
} Mallard_t;

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

    thisMallard->parentDuck = duckCreate();
    duckInit( thisMallard->parentDuck, name );

    thisMallard->myColor = color;
}

char *
mallardGetName( Mallard thisMallard )
{
    return duckGetName( thisMallard->parentDuck );
}

void
mallardQuack( Mallard thisMallard )
{
    printf("\t%s: Quack!\n", duckGetName(thisMallard->parentDuck));
}

void
mallardShow( Mallard thisMallard )
{
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", duckGetName(thisMallard->parentDuck), colorNames[thisMallard->myColor]);
}

const char *
mallardGetColor( Mallard thisMallard )
{
    return colorNames[thisMallard->myColor];
}

void
mallardMigrate( Mallard thisMallard )
{
    printf("\t%s: I'm migrating!\n", duckGetName(thisMallard->parentDuck));
}
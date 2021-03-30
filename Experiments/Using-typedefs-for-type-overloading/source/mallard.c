#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"
#include "mallard.h"
#include "mallard.r"

const char * colorNames[] = {"red", "brown", "white"};

static void mallardShow( Duck thisDuck );
static void _mallardMigrate( Mallard_t * thisMallard );

static Mallard_Interface_Struct interface = {
    {.show=mallardShow},
    _mallardMigrate
};

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

    duckInit( thisMallard, name );

    thisMallard->vtable = (Duck_Interface)&interface;
    ((Mallard_t *)(thisMallard))->myColor = color;
}

static void
mallardShow( Mallard thisMallard )
{
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", thisMallard->name, colorNames[((Mallard_t *)(thisMallard))->myColor]);
}

void
mallardMigrate( Mallard thisMallard )
{
    if ( thisMallard && thisMallard->vtable && ((Mallard_Interface)(thisMallard->vtable))->migrate )
    {
        ((Mallard_Interface)(thisMallard->vtable))->migrate((Mallard_t *)thisMallard);
    }
}

static void
_mallardMigrate( Mallard_t * thisMallard )
{
    printf("\t%s: I'm migrating!\n", ((Duck)thisMallard)->name);
}
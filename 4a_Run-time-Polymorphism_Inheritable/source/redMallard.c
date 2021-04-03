#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"
#include "mallard.h"
#include "redMallard.h"
#include "redMallard.r"

static void redMallardShow( Duck thisDuck );
static void redMallardMigrate( Mallard thisMallard );

static Mallard_Interface_Struct interface = {
    {.show=redMallardShow},
    redMallardMigrate
};

redMallard
redMallardCreate( void )
{
    redMallard newRedMallard = (redMallard)malloc(sizeof(redMallard_t));
    // TODO: Check for null pointer on malloc failure

    return newRedMallard;
}

void
redMallardInit( redMallard thisRedMallard, char * name, featherColor color )
{
    printf("\tInitializing new red-breasted mallard with name: %s\n", name);

    mallardInit( &thisRedMallard->parentMallard, name, color );

    thisRedMallard->parentMallard.parentDuck.vtable = (Duck_Interface)&interface;
}

static void
redMallardShow( Duck thisDuck )
{
    Mallard thisMallard = (Mallard)thisDuck;
    printf("\tHi! I'm a red-breasted mallard duck. My name is %s. I have %s feathers.\n", thisDuck->name, colorNames[thisMallard->myColor]);
}

static void
redMallardMigrate( Mallard thisMallard )
{
    Duck thisDuck = (Duck)thisMallard;
    printf("\t%s: I'm migrating from North to South America with my fellow red-breasted mallards!\n", thisDuck->name);
}
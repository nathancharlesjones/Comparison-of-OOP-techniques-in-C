#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "duck.h"
#include "duckInterface.h"
#include "mallard.h"
#include "mallardInterface.h"
#include "redMallard.h"

typedef struct redMallard_t
{
    Mallard parentMallard;
} redMallard_t;

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

    thisRedMallard->parentMallard = mallardCreate();
    mallardInit( thisRedMallard->parentMallard, name, color );
}

void
_redMallardQuack( redMallard thisRedMallard )
{
    printf("\t%s: Quack!\n", duckGetName(thisRedMallard->parentMallard));
}

void
_redMallardShow( redMallard thisRedMallard )
{
    Mallard thisMallard = thisRedMallard->parentMallard;
    printf("\tHi! I'm a red-breasted mallard duck. My name is %s. I have %s feathers.\n", duckGetName(thisMallard), mallardGetColor(thisMallard));
}

const char *
_redMallardGetColor( redMallard thisRedMallard )
{
    return mallardGetColor( thisRedMallard->parentMallard );
}

void
_redMallardMigrate( redMallard thisRedMallard )
{
    Mallard thisMallard = thisRedMallard->parentMallard;
    printf("\t%s: I'm migrating from North to South America with my fellow red-breasted mallards!\n", duckGetName(thisMallard));
}
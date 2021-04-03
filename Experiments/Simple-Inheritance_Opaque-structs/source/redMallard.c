#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "assert.h"
#include "oopUtils.h"
#include "duck.h"
#include "mallard.h"
#include "redMallard.h"
#include "redMallard.r"

static void redMallardShow( void *thisDuck );
static void redMallardMigrate( void * thisMallard );

redMallard_Interface_Struct redMallardDef = {
/*  /----------------------Mallard_t-----------------------\
      /--------------Duck_t-----------\
        /--BaseClass-\                                      */
    { { { &mallardDef }, redMallardShow}, redMallardMigrate }
};

redMallard_Interface redMallard = &redMallardDef;

bool
isRedMallard( void * thisRedMallard )
{
    bool ret = false;

    ASSERT(thisRedMallard);

    void * thisType = GET_TYPE_FROM_OBJ(thisRedMallard);

    while( thisType && thisType != redMallard )
    {
        thisType = (void *)GET_PARENT_FROM_TYPE(thisType);
    }

    if( thisType == redMallard ) ret = true;

    return ret;
}

void *
redMallardCreate( void )
{
    void * newRedMallard = (redMallard_t *)malloc(sizeof(redMallard_t));
    // TODO: Check for null pointer on malloc failure

    return newRedMallard;
}

void
redMallardInit( void * thisRedMallard, char * name, featherColor color )
{
    ASSERT(thisRedMallard);
    ASSERT(name);

    redMallard_t * _thisRedMallard = (redMallard_t *)thisRedMallard;

    printf("\tInitializing new red-breasted mallard with name: %s\n", name);

    mallardInit( &_thisRedMallard->parentMallard, name, color );

    _thisRedMallard->parentMallard.parentDuck.vtable = (Duck_Interface)redMallard;
}

static void
redMallardShow( void * thisDuck )
{
    ASSERT(thisDuck);
    ASSERT(isRedMallard(thisDuck));

    // Once ASSERT has been replaced with something that will actually
    // halt program execution, this guard clause could/should be
    // removed.
    if( isRedMallard(thisDuck) )
    {
        Mallard_t * thisMallard = (Mallard_t *)thisDuck;
        printf("\tHi! I'm a red-breasted mallard duck. My name is %s. I have %s feathers.\n", thisMallard->parentDuck.name, colorNames[thisMallard->myColor]);
    }
}

static void
redMallardMigrate( void * thisMallard )
{
    ASSERT(thisMallard);
    ASSERT(isRedMallard(thisMallard)); //should be unnecessary since this function is only ever called
    // by way of "mallardMigrate()", which confirms that the object is a Mallard. I leave it in
    // because it "feels" right.

    Duck_t * thisDuck = (Duck_t *)thisMallard;
    printf("\t%s: I'm migrating from North to South America with my fellow red-breasted mallards!\n", thisDuck->name);
}
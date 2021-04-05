#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "assert.h"
#include "oopUtils.h"
#include "duck.h"
#include "mallard.h"
#include "mallard.r"

const char * colorNames[] = {"red", "brown", "white"};

static void mallardShow( void * thisDuck );
static void _mallardMigrate( void * thisMallard );

Mallard_Interface_Struct mallardDef = {
/*  /----------Duck_t-----------\
      /-BaseClass-\               */
    { { &duckDef }, mallardShow },
    _mallardMigrate
};

Mallard_Interface Mallard = &mallardDef;

bool
isMallard( void * thisMallard )
{
    bool ret = false;

    ASSERT(thisMallard);

    void * thisType = GET_TYPE_FROM_OBJ(thisMallard);

    while( thisType && thisType != Mallard )
    {
        thisType = (void *)GET_PARENT_FROM_TYPE(thisType);
    }

    if( thisType == Mallard ) ret = true;

    return ret;
}

void *
mallardCreate( void )
{
    void * newMallard = (Mallard_t *)malloc(sizeof(Mallard_t));
    // TODO: Check for null pointer on malloc failure

    return newMallard;
}

void
mallardInit( void * thisMallard, char * name, featherColor color )
{
    ASSERT(thisMallard);
    ASSERT(name);

    Mallard_t * _thisMallard = (Mallard_t *)thisMallard;

    printf("\tInitializing new mallard duck with name: %s\n", name);

    duckInit( &_thisMallard->parentDuck, name );

    _thisMallard->parentDuck.vtable = (Duck_Interface)Mallard;
    _thisMallard->myColor = color;
}

static void
mallardShow( void * thisDuck )
{
    ASSERT(thisDuck);
    ASSERT(isMallard(thisDuck));

    // Once ASSERT has been replaced with something that will actually
    // halt program execution, this guard clause could/should be
    // removed.
    if( isMallard(thisDuck) )
    {
        Mallard_t * thisMallard = (Mallard_t *)thisDuck;
        printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", thisMallard->parentDuck.name, colorNames[thisMallard->myColor]);
    }
}

void
mallardMigrate( void * thisMallard )
{
    ASSERT(thisMallard);
    ASSERT(isMallard(thisMallard));

    // Once ASSERT has been replaced with something that will actually
    // halt program execution, this guard clause could/should be
    // removed.
    if( isMallard(thisMallard) )
    {
        Mallard_t * _thisMallard = (Mallard_t *)thisMallard;

        if ( _thisMallard && _thisMallard->parentDuck.vtable && ((Mallard_Interface)(_thisMallard->parentDuck.vtable))->migrate )
        {
            ((Mallard_Interface)(_thisMallard->parentDuck.vtable))->migrate(thisMallard);
        }
    }
}

static void
_mallardMigrate( void * thisMallard )
{
    ASSERT(thisMallard);
    ASSERT(isMallard(thisMallard)); //should be unnecessary since this function is only ever called
    // by way of "mallardMigrate()", which confirms that the object is a Mallard. I leave it in
    // because it "feels" right.

    Duck_t * thisDuck = (Duck_t *)thisMallard;
    printf("\t%s: I'm migrating!\n", thisDuck->name);
}
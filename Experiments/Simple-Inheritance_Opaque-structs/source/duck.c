#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "oopUtils.h"
#include "assert.h"
#include "duck.h"
#include "duck.r"

static void _duckShow( void * thisDuck );

Duck_Interface_Struct duckDef = {
    { NULL },
    _duckShow
};

Duck_Interface Duck = &duckDef;

bool
isDuck( void * thisDuck )
{
    bool ret = false;

    ASSERT(thisDuck);

    void * thisType = GET_TYPE_FROM_OBJ(thisDuck);

    while( thisType && thisType != Duck )
    {
        thisType = (void *)GET_PARENT_FROM_TYPE(thisType);
    }

    if( thisType == Duck ) ret = true;

    return ret;
}

void *
duckCreate( void )
{
    Duck_t * newDuck = (Duck_t *)malloc(sizeof(Duck_t));
    // TODO: Check for null pointer on malloc failure

    return (void *)newDuck;
}

void
duckInit( void * thisDuck, char * name )
{
    ASSERT(thisDuck);
    ASSERT(name);

    Duck_t * _thisDuck = (Duck_t *)thisDuck;

    printf("\tInitializing duck with name: %s\n", name);

    _thisDuck->vtable = Duck;
    strncpy(_thisDuck->name, name, MAX_CHARS_NAME);
}

void
duckQuack( void * thisDuck )
{
    ASSERT(thisDuck);
    //ASSERT(isDuck(thisDuck));
    
    // This should probably be an ASSERT, like above
    if( isDuck(thisDuck) )
    {
        Duck_t * _thisDuck = (Duck_t *)thisDuck;

        printf("\t%s: Quack!\n", _thisDuck->name);
    }
}

void
duckShow( void * thisDuck )
{
    ASSERT(thisDuck);
    //ASSERT(isDuck(thisDuck));
    
    // This should probably be an ASSERT, like above
    if( isDuck(thisDuck) )
    {    
        Duck_t * _thisDuck = (Duck_t *)thisDuck;

        if ( _thisDuck && _thisDuck->vtable && _thisDuck->vtable->show )
        {
            _thisDuck->vtable->show(thisDuck);
        }
    }
}

static void
_duckShow( void * thisDuck )
{
    ASSERT(thisDuck);
    // ASSERT(isDuck(thisDuck)) should be unnecessary since this function is only ever called
    // by way of "duckShow()", which confirms that the object is a Duck.

    Duck_t * _thisDuck = (Duck_t *)thisDuck;

    printf("\tHi! My name is %s.\n", _thisDuck->name);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "duck.h"
#include "mallard.h"

const char * colorNames[] = {"red", "brown", "white"};

typedef struct Mallard_t
{
    uint8_t parentDuck[sizeof_Duck_t];
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

    // Problem gets exposed (possibly) here: "thisMallard" was
    // aligned using it's size, but may not be aligned based on
    // the size of "Duck_t". Casting "thisMallard" to type "Duck"
    // may result in an unaligned memory access.
    duckInit( (Duck)thisMallard, name );

    thisMallard->myColor = color;
}

void
mallardShow( Mallard thisMallard )
{
    // Problem gets exposed (possibly) here: "thisMallard" was
    // aligned using it's size, but may not be aligned based on
    // the size of "Duck_t". Casting "thisMallard" to type "Duck"
    // may result in an unaligned memory access.
    printf("\tHi! I'm a mallard duck. My name is %s. I have %s feathers.\n", duckGetName((Duck)thisMallard), colorNames[thisMallard->myColor]);
}
#include <stdio.h>
#include "duck.h"
#include "mallard.h"

int
main( void )
{
    printf("-----2_Simple Inheritance-----\n");
    
    Duck George = duckCreate();
    Mallard Bill = mallardCreate();
    
    printf("|__Initializing mallard objects:\n");

    duckInit(George, "George");
    mallardInit(Bill, "Bill", BROWN);

    printf("|__Showing duck and mallard objects:\n");
    
    duckShow(George);
    mallardShow(Bill);
    
    printf("|__Showing mallard objects (cast to duck objects):\n");
    
    duckShow((Duck)Bill);

    return 0;
}
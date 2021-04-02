#include <stdio.h>
#include "duck.h"
#include "mallard.h"

int
main( void )
{    
    Duck George = duckCreate_static();
    Mallard Bill = mallardCreate_dynamic();
    
    printf("|__Initializing mallard objects:\n");

    duckInit(George, "George");
    mallardInit(Bill, "Bill", BROWN);

    printf("|__Showing duck and mallard objects:\n");
    
    duckShow(George);
    mallardShow(Bill);
    
    printf("|__Showing mallard objects (cast to duck objects):\n");
    
    duckShow((Duck)Bill);

    printf("|__Destroying duck and mallard objects:\n");

    duckDestroy_static(George);
    mallardDestroy_dynamic(Bill);

    return 0;
}
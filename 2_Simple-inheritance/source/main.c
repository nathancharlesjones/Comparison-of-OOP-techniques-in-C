#include <stdio.h>
#include "duck.h"
#include "mallard.h"

int
main( void )
{    
    printf("|__Creating duck and mallard objects\n");
    
    Duck George = duckCreate_static();
    Mallard Bill = mallardCreate_dynamic();
    
    printf("|__Initializing duck and mallard objects:\n");

    duckInit(George, "George");
    mallardInit(Bill, "Bill", BROWN);

    printf("|__Showing duck and mallard objects:\n");
    
    duckShow(George);
    mallardShow(Bill);
    
    printf("|__Showing mallard objects (cast to duck objects):\n");
    
    duckShow((Duck)Bill);

    printf("|__Deinitializing duck and mallard objects:\n");

    duckDeinit(George);
    mallardDeinit(Bill);

    printf("|__Destroying duck and mallard objects\n");

    duckDestroy_static(George);
    mallardDestroy_dynamic(Bill);

    return 0;
}
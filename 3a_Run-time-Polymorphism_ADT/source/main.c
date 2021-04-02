#include <stdio.h>
#include "duck.h"
#include "mallard.h"

int
main( void )
{    
    printf("|__Creating duck and mallard objects\n");

    Duck George = duckCreate_dynamic();
    Duck Bill = mallardCreate_static();
    
    printf("|__Initializing duck and mallard objects:\n");

    duckInit(George, "George");
    mallardInit(Bill, "Bill", BROWN);

    printf("|__Quacking duck and mallard objects:\n");
    
    duckQuack(George);
    duckQuack(Bill);
    
    printf("|__Showing duck and mallard objects:\n");
    
    duckShow(George);
    duckShow(Bill);

    printf("|__Deinitializing duck and mallard objects:\n");

    duckDeinit(George);
    mallardDeinit(Bill);

    printf("|__Destroying duck and mallard objects\n");

    duckDestroy_dynamic(George);
    mallardDestroy_static(Bill);
    
    return 0;
}
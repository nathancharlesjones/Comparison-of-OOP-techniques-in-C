#include <stdio.h>
#include "duck.h"
#include "rubber.h"
#include "mallard.h"

int
main( void )
{    
    printf("|__Creating mallard and rubber duck objects\n");

    Duck George = rubberCreate_dynamic("George", MEDIUM);
    Duck Bill = mallardCreate_static("Bill", BROWN);

    printf("|__Quacking duck and mallard objects:\n");
    
    duckQuack(George);
    duckQuack(Bill);
    
    printf("|__Showing duck and mallard objects:\n");
    
    duckShow(George);
    duckShow(Bill);

    printf("|__Destroying duck and mallard objects\n");

    duckDestroy(George);
    duckDestroy(Bill);
    
    return 0;
}
#include <stdio.h>
#include "duck.h"
#include "mallard.h"

int
main( void )
{
    printf("-----3_ADT-----\n");
    
    Duck George = duckCreate();
    Duck Bill = mallardCreate();
    
    printf("|__Initializing duck and mallard objects:\n");

    duckInit(George, "George");
    mallardInit(Bill, "Bill", BROWN);

    printf("|__Quacking duck and mallard objects:\n");
    
    duckQuack(George);
    duckQuack(Bill);
    
    printf("|__Showing duck and mallard objects:\n");
    
    duckShow(George);
    duckShow(Bill);
    
    return 0;
}
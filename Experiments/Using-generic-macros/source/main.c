#include <stdio.h>
#include "duck.h"
#include "duckInterface.h"
#include "mallard.h"
#include "mallardInterface.h"
#include "redMallard.h"

int
main( void )
{    
    Duck George = duckCreate();
    Mallard Bill = mallardCreate();
    redMallard Mary = redMallardCreate();
    
    printf("|__Initializing duck and mallard objects:\n");

    duckInit(George, "George");
    mallardInit(Bill, "Bill", BROWN);
    redMallardInit(Mary, "Mary", WHITE);

    printf("|__Quacking duck and mallard objects:\n");
    
    duckQuack(George);
    duckQuack(Bill);
    duckQuack(Mary);

    printf("|__Showing duck and mallard objects:\n");
    
    duckShow(George);
    duckShow(Bill);
    duckShow(Mary);

    printf("|__Migrating mallard objects:\n");

    mallardMigrate(Bill);
    mallardMigrate(Mary);
    
    return 0;
}
#include <stdio.h>
#include "duck.h"
#include "mallard.h"
#include "redMallard.h"

int
main( void )
{   
    printf("|__Creating duck and mallard objects:\n");

    void * George = duckCreate_dynamic("George");
    void * Bill = mallardCreate_static("Bill", BROWN);
    void * Mary = redMallardCreate_dynamic("Mary", WHITE);
    
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

    printf("|__Destroying duck and mallard objects\n");

    duckDestroy(George);
    duckDestroy(Bill);
    duckDestroy(Mary);

    return 0;
}
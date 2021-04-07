#include <stdio.h>
#include "duck.h"
#include "mallard.h"
#include "redMallard.h"

int
main( void )
{    
    printf("|__Creating duck object\n");

    void * George = duckCreate(duckFromHeapMem, "George");
    void * Bill = duckCreate(mallardFromStaticMem, "Bill", BROWN);
    void * Mary = duckCreate(redMallardFromStaticMem, "Mary", RED);
    
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

    printf("|__Destroying duck and mallard objects:\n");

    duckDestroy(George);
    duckDestroy(Bill);
    duckDestroy(Mary);

    printf("|__Intentionally calling mallard functions on duck objects (to test the 'type-checking'):\n");

    void * Helen = duckCreate(duckFromHeapMem, "Helen");
    mallardMigrate(Helen);

    return 0;
}
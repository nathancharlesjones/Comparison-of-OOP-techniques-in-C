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
    //void * Mary = redMallardCreate();
    
    printf("|__Quacking duck and mallard objects:\n");
    
    duckQuack(George);
    duckQuack(Bill);
    //duckQuack(Mary);

    printf("|__Showing duck and mallard objects:\n");
    
    duckShow(George);
    duckShow(Bill);
    //duckShow(Mary);

    printf("|__Migrating mallard objects:\n");

    mallardMigrate(Bill);
    //mallardMigrate(Mary);

    printf("|__Intentionally calling mallard functions on duck objects:\n");

    mallardMigrate(George);

    return 0;
}
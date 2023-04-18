#include <stdio.h>
#include "duck.h"
#include "mallard.h"
#include "redMallard.h"

int
main( void )
{   
    printf("|__Creating duck and mallard objects:\n");

    Duck George = duckCreate_dynamic("George");
    Mallard Bill = mallardCreate_static("Bill", BROWN);
    redMallard Mary = redMallardCreate_dynamic("Mary", WHITE);
    
    printf("|__Quacking duck and mallard objects:\n");
    
    duckQuack(George);
    duckQuack((Duck)Bill);
    // "duckQuack(Bill)" also works, you'll just have to endure compiler warnings about implicit casts
    duckQuack((Duck)Mary);

    printf("|__Showing duck and mallard objects:\n");
    
    duckShow(George);
    duckShow((Duck)Bill);
    // "duckShow(Bill)" also works, you'll just have to endure compiler warnings about implicit casts
    duckShow((Duck)Mary);
    // "duckShow(Mary)" also works, you'll just have to endure compiler warnings about implicit casts

    printf("|__Migrating mallard objects:\n");

    mallardMigrate(Bill);
    mallardMigrate((Mallard)Mary);
    // "mallardMigrate(Mary)" also works, you'll just have to endure compiler warnings about implicit casts

    printf("|__Destroying duck and mallard objects\n");

    duckDestroy(George);
    duckDestroy((Duck)Bill);
    // "duckDestroy(Bill)" also works, you'll just have to endure compiler warnings about implicit casts
    duckDestroy((Duck)Mary);
    // "duckDestroy(Mary)" also works, you'll just have to endure compiler warnings about implicit casts

    return 0;
}
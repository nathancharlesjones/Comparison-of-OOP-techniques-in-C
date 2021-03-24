#include <stdio.h>
#include "duck.h"
#include "mallard.h"
#include "redMallard.h"

int
main( void )
{
    printf("-----4_Polymorphism-----\n");
    
    Duck George = duckCreate();
    Mallard Bill = mallardCreate();
    redMallard Mary = redMallardCreate();
    
    printf("|__Initializing duck and mallard objects:\n");

    duckInit(George, "George");
    mallardInit(Bill, "Bill", BROWN);
    redMallardInit(Mary, "Mary", WHITE);

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

    printf("|__Migrating mallard objects:\n");

    mallardMigrate(Bill);
    mallardMigrate((Mallard)Mary);
    // "mallardMigrate(Mary)" also works, you'll just have to endure compiler warnings about implicit casts

    return 0;
}
#include <stdio.h>
#include "duck.h"
#include "mallard.h"

int
main( void )
{    
    printf("|__Creating duck and mallard objects\n");

    Duck George = duckCreate(duckFromStaticMem, "George");
    //Duck George = duckCreate_dynamic();
    //Duck Bill = mallardCreate_static();

    printf("|__Quacking duck and mallard objects:\n");
    
    duckQuack(George);
    //duckQuack(Bill);
    
    printf("|__Showing duck and mallard objects:\n");
    
    duckShow(George);
    //duckShow(Bill);

    printf("|__Destroying duck and mallard objects\n");

    duckDestroy(George);
    //duckDestroy_dynamic(George);
    //mallardDestroy_static(Bill);
    
    return 0;
}
#include <stdio.h>
#include "duck.h"

int
main( void )
{
    printf("|__Creating duck object (singular):\n");

    duckInit("Huey");

    printf("|__Showing duck object (singular):\n");
    
    duckShow();

    return 0;
}
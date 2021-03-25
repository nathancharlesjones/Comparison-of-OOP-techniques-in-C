#include <stdio.h>
#include "duck.h"

int
main( void )
{
    printf("|__Creating duck objects:\n");

    Duck Huey = duckCreate();
    Duck Dewey = duckCreate();
    Duck Louie = duckCreate();

    duckInit(Huey, "Huey");
    duckInit(Dewey, "Duey");
    duckInit(Louie, "Luey");

    printf("|__Showing duck objects:\n");
    
    duckShow(Huey);
    duckShow(Dewey);
    duckShow(Louie);

    return 0;
}
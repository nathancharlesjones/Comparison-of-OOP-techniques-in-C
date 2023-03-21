#include <stdio.h>
#include "duck.h"

int
main( void )
{
    printf("|__Creating duck objects:\n");

    Duck Huey = duckCreate_dynamic();
    Duck Dewey = duckCreate_dynamic();
    Duck Louie = duckCreate_static();

    duckInit(Huey, "Huey");
    duckInit(Dewey, "Dewey");
    duckInit(Louie, "Louie");

    printf("|__Showing duck objects:\n");
    
    duckShow(Huey);
    duckShow(Dewey);
    duckShow(Louie);

    printf("|__Destroying duck objects:\n");

    duckDestroy_dynamic(Huey);
    duckDestroy_dynamic(Dewey);
    duckDestroy_static(Louie);

    return 0;
}
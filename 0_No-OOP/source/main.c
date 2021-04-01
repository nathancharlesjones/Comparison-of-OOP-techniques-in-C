#include <stdio.h>
#include "duck.h"

int
main( void )
{
    printf("|__Creating duck objects:\n");

    Duck_t * Huey = duckCreate();
    Duck_t * Dewey = duckCreate();
    Duck_t * Louie = duckCreate();

    duckInit(Huey, "Huey");
    duckInit(Dewey, "Dewey");
    duckInit(Louie, "Louie");

    printf("|__Showing duck objects:\n");
    
    duckShow(Huey);
    duckShow(Dewey);
    duckShow(Louie);

    printf("|__Printing duck objects by directly accessing their names:\n");
    
    printf("\tAccessing name directly for: %s\n", Huey->name);
    printf("\tAccessing name directly for: %s\n", Dewey->name);
    printf("\tAccessing name directly for: %s\n", Louie->name);

    printf("|__Destroying duck objects:\n");

    duckDestroy(Huey);
    duckDestroy(Dewey);
    duckDestroy(Louie);

    return 0;
}
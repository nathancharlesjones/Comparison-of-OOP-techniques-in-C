#include <stdio.h>
#include "duck.h"

int
main( void )
{
    printf("|__Creating duck objects:\n");

    p_Duck_t Huey = duckCreate();
    p_Duck_t Dewey = duckCreate();
    p_Duck_t Louie = duckCreate();

    duckInit(Huey, "Huey");
    duckInit(Dewey, "Dewey");
    duckInit(Louie, "Louie");

    printf("|__Showing duck objects:\n");
    
    duckShow(Huey);
    duckShow(Dewey);
    duckShow(Louie);

    // Can't write the following code; the compiler will 
    // complain of incomplete data types since we've hidden
    // the Duck_t struct inside duck.c

    /*
    printf("|__Printing duck objects by directly accessing their names:\n");
    
    printf("\tAccessing name directly for: %s\n", Huey->name);
    printf("\tAccessing name directly for: %s\n", Dewey->name);
    printf("\tAccessing name directly for: %s\n", Louie->name);
    */

    printf("|__Destroying duck objects:\n");

    duckDestroy(Huey);
    duckDestroy(Dewey);
    duckDestroy(Louie);

    return 0;
}
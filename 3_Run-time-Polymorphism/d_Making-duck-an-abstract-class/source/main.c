#include <stdio.h>
#include "assert.h"
#include "duck.h"
#include "mallard.h"
#include "rubber.h"

int
main( void )
{
    printf("|__Creating duck objects:\n");

    p_Duck_t Huey = mallardNew("Huey", WHITE);
    p_Duck_t Dewey = rubberNew("Dewey", SMALL);
    p_Duck_t Louie = mallardNew("Louie", RED);

    printf("|__Quacking duck objects:\n");
    
    duckQuack(Huey);
    duckQuack(Dewey);
    duckQuack(Louie);

    printf("|__Showing duck objects:\n");
    
    duckShow(Huey);
    duckShow(Dewey);
    duckShow(Louie);

    printf("|__Destroying duck objects:\n");

    duckDestroy(Huey);
    duckDestroy(Dewey);
    duckDestroy(Louie);

    return 0;
}
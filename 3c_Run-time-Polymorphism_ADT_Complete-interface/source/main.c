#include <stdio.h>
#include <string.h>
#include "duck.h"
#include "mallard.h"

Duck duckFromCliArgs( int argc, char * argv[] );

int
main( int argc, char * argv[] )
{   
    printf("|__Creating duck object\n");

    Duck myDuck = duckFromCliArgs( argc, argv );

    printf("|__Quacking duck object:\n");
    
    duckQuack(myDuck);
    
    printf("|__Showing duck object:\n");
    
    duckShow(myDuck);

    printf("|__Destroying duck object\n");

    duckDestroy(myDuck);
    
    return 0;
}

Duck
duckFromCliArgs( int argc, char * argv[] )
{
    Duck newDuck = NULL;

    char * duck_interface = argv[1];
    char * name = argv[2];

    if( 0 == strcmp(duck_interface,"dh"))
    {
        newDuck = duckCreate(duckFromHeapMem, name);
    }
    else if( 0 == strcmp(duck_interface, "ds") )
    {
        newDuck = duckCreate(duckFromStaticMem, name);
    }
    else
    {
        char * feathers = argv[3];
        featherColor myColor = 0;
        if( 0 == strcmp(feathers, "red") )
        {
            myColor = RED;
        }
        else if( 0 == strcmp(feathers, "brown") )
        {
            myColor = BROWN;
        }
        else
        {
            myColor = WHITE;
        }

        if( 0 == strcmp(duck_interface, "mh") )
        {
            newDuck = duckCreate(mallardFromHeapMem, name, myColor);
        }
        else if( 0 == strcmp(duck_interface, "ms") )
        {
            newDuck = duckCreate(mallardFromStaticMem, name, myColor);
        }
    }

    return newDuck;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS_NAME 10
#define MAX_CHARS_NAME_WITH_NUL (MAX_CHARS_NAME+1)

typedef struct Duck_t
{
    char name[MAX_CHARS_NAME_WITH_NUL];
} Duck_t;

Duck_t *    duckNew( char * name );
void        duckShow( Duck_t * thisDuck );
void        duckDestroy( Duck_t * thisDuck );

int
main( void )
{
    printf("|__Creating duck objects:\n");

    Duck_t * Huey = duckNew("Huey");
    Duck_t * Dewey = duckNew("Dewey");
    Duck_t * Louie = duckNew("Louie");

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

Duck_t *
duckNew( char * name )
{
    Duck_t * newDuck = (Duck_t *)calloc(1, sizeof(Duck_t));
    // TODO: Check for null pointer on malloc failure

    printf("\tInitializing new duck with name: %s\n", name);

    memset(newDuck, 0, sizeof(Duck_t));
    strncpy(newDuck->name, name, MAX_CHARS_NAME);

    return newDuck;
}

void
duckShow( Duck_t * thisDuck )
{
    printf("\tHi! My name is %s.\n", thisDuck->name);
}

void
duckDestroy( Duck_t * thisDuck )
{
    printf("\tDestroying Duck object with name: %s\n", thisDuck->name);
    memset(thisDuck, 0, sizeof(Duck_t));
    free(thisDuck);
}
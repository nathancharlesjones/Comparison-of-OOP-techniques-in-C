#ifndef DUCK_PRIVATE_H
#define DUCK_PRIVATE_H

typedef struct Duck_t
{
    void (*duckShow)( p_Duck_t thisDuck );
    char name[MAX_CHARS_NAME_WITH_NUL];
} Duck_t;

/****************************************************************
 * Accessor functions (for better decoupling of derived classes)
 ****************************************************************/

/*

Option 1: Function-like macro

#define name(duck) (((*Duck_t)(duck))->name)


Option 2: Getter/setter functions

char *
duckGetName( p_Duck_t thisDuck )
{
    ASSERT(thisDuck && name);
    return thisDuck->name;
}

void
duckSetName( p_Duck_t thisDuck )
{
    strncpy(newDuck->name, name, MAX_CHARS_NAME);
}

*/

#endif // DUCK_PRIVATE_H
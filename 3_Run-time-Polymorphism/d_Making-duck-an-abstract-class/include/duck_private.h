#ifndef DUCK_PRIVATE_H
#define DUCK_PRIVATE_H

#include <string.h>

typedef struct Duck_interface_struct
{
    void (*show)( p_Duck_t thisDuck );
    void (*deinit)( p_Duck_t thisDuck );
    void (*destroy)( p_Duck_t thisDuck );
} Duck_interface_struct;

typedef struct Duck_t
{
    const struct Duck_interface_struct * vtable;
    char name[MAX_CHARS_NAME_WITH_NUL];
} Duck_t;

static inline void
duckInit( struct Duck_t * thisDuck, char * name )
{
    ASSERT(thisDuck && name);
    printf("\tInitializing new duck with name: %s\n", name);
    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

/****************************************************************
 * Accessor functions (for better decoupling of derived classes)
 ****************************************************************/

/*

Option 1: Function-like macro

#define name(duck) (((struct Duck_t *)(duck))->name)


Option 2: Getter/setter functions

char *
duckGetName( struct Duck_t * thisDuck )
{
    ASSERT(thisDuck && name);
    return thisDuck->name;
}

void
duckSetName( struct Duck_t * thisDuck )
{
    strncpy(thisDuck->name, name, MAX_CHARS_NAME);
}

*/

#endif // DUCK_PRIVATE_H
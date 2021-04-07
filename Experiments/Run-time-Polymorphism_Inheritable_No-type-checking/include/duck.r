#ifndef DUCK_R
#define DUCK_R

#include <stdarg.h>

#define MAX_CHARS_NAME 10
#define MAX_CHARS_NAME_WITH_NUL (MAX_CHARS_NAME+1)

typedef struct Duck_Interface_Struct const * Duck_Interface;

typedef struct Duck_t
{
    Duck_Interface vtable;
    char name[MAX_CHARS_NAME_WITH_NUL];
} Duck_t, *Duck;

typedef struct Duck_Interface_Struct
{
    void (*show)( void * thisDuck );
    void (*deinit)( void * thisDuck );
    void (*destroy)( void * thisDuck );
} Duck_Interface_Struct;

void duckInit( Duck thisDuck, char * name );
void duckDeinit( void * thisDuck );

#endif // DUCK_R
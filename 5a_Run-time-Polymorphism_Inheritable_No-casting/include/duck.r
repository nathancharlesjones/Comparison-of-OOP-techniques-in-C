#ifndef DUCK_R
#define DUCK_R

#include <stdarg.h>
#include "duck.h"

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
    void * (*getParentInterface)( void );
    void * (*create)( va_list * args );
    void (*destroy)( void * self );
    void (*show)( Duck thisDuck );
} Duck_Interface_Struct;

void duckInit( Duck thisDuck, va_list * args );
void duckDeinit( Duck thisDuck );

#endif // DUCK_R
#ifndef DUCK_R
#define DUCK_R

#include <stdarg.h>
#include <stdint.h>
#include "duck.h"

#define MAX_CHARS_NAME 10
#define MAX_CHARS_NAME_WITH_NUL (MAX_CHARS_NAME+1)
#define MAGIC 0x0EFFACED // efface: to make (oneself) modestly or shyly inconspicuous (shamelessly stolen from "OOP in ANSI C" by Axel Schreiner)

typedef struct Duck_Interface_Struct const * Duck_Interface;

typedef struct Duck_t
{
    Duck_Interface vtable;
    uint32_t magic_number;
    char name[MAX_CHARS_NAME_WITH_NUL];
} Duck_t, *Duck;

typedef struct Duck_Interface_Struct
{
    uint32_t magic_number;
    void * (*getParentInterface)( void );
    void * (*create)( Duck_Interface newDuckType, va_list * args );
    void (*destroy)( void * self );
    void (*show)( Duck thisDuck );  // Optional for derived classes; set to "0" or "NULL" to use the default "Duck" implementation
} Duck_Interface_Struct;

void duckInit( Duck thisDuck, va_list * args );
void duckDeinit( Duck thisDuck );

#endif // DUCK_R
#ifndef DUCK_R
#define DUCK_R

#include <stdarg.h>

#define MAX_CHARS_NAME 10

typedef struct Duck_Interface_Struct * Duck_Interface;

typedef struct Duck_t
{
    Duck_Interface vtable;
    char name[MAX_CHARS_NAME];
} Duck_t;

typedef struct Duck_Interface_Struct
{
    Duck_t * (*create)( void );
    void (*init)( Duck_t * thisDuck, va_list * args );
    void (*show)( Duck_t * thisDuck );
    void (*deinit)( Duck_t * thisDuck );
    void (*destroy)( Duck_t * thisDuck );
} Duck_Interface_Struct;

#endif // DUCK_R
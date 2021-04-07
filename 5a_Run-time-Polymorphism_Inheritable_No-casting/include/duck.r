#ifndef DUCK_R
#define DUCK_R

#include "baseClass.r"
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
    BaseClass_Interface_Struct baseInterface;
    void (*show)( Duck thisDuck );
} Duck_Interface_Struct;

#endif // DUCK_R
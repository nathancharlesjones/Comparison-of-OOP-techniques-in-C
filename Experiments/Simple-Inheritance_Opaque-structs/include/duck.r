#ifndef DUCK_R
#define DUCK_R

#include "baseClass.r"

#define MAX_CHARS_NAME 10

typedef struct Duck_Interface_Struct * Duck_Interface;

typedef struct Duck_t
{
    Duck_Interface vtable;
    char name[MAX_CHARS_NAME];
} Duck_t;

typedef struct Duck_Interface_Struct
{
    BaseClass_Interface_Struct baseClass;
    void (*show)( void * thisDuck );
} Duck_Interface_Struct;

extern Duck_Interface_Struct duckDef;

#endif // DUCK_R
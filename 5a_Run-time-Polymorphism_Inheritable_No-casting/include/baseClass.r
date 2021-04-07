#ifndef BASE_CLASS_R
#define BASE_CLASS_R

#include <stdarg.h>

typedef struct BaseClass_Interface_Struct * BaseClass_Interface;

typedef struct BaseClass_Interface_Struct
{
    void * (*getParentInterface)( void );
    void * (*create)( va_list * args );
    void (*destroy)( void * self );
} BaseClass_Interface_Struct;

#endif // BASE_CLASS_R
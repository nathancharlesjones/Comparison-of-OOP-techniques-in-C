#ifndef BASE_CLASS_R
#define BASE_CLASS_R

#include <stdarg.h>

typedef struct BaseClass_Interface_Struct * BaseClass_Interface;

typedef struct BaseClass_Interface_Struct
{
    void * (*getParentInterface)( void );
    void * (*create)( void );
    void (*init)( void * self, va_list * args );
    void (*deinit)( void * self );
    void (*destroy)( void * self );
} BaseClass_Interface_Struct;

#endif // BASE_CLASS_R
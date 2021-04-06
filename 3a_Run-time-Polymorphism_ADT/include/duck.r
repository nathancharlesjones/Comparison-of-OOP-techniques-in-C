#ifndef DUCK_R
#define DUCK_R

#define MAX_CHARS_NAME 10
#define MAX_CHARS_NAME_WITH_NUL (MAX_CHARS_NAME+1)

typedef struct Duck_Interface_Struct const * Duck_Interface;

typedef struct Duck_t
{
    Duck_Interface vtable;
    char name[MAX_CHARS_NAME_WITH_NUL];
} Duck_t;

typedef struct Duck_Interface_Struct
{
    void (*show)( Duck_t * thisDuck );
    void (*deinit)( Duck_t * thisDuck );
    void (*destroy)( Duck_t * thisDuck );
} Duck_Interface_Struct;

#endif // DUCK_R
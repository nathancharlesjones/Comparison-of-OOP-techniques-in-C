#ifndef DUCK_R
#define DUCK_R

#define MAX_CHARS_NAME 10
#define MAX_CHARS_NAME_WITH_NUL (MAX_CHARS_NAME+1)

typedef struct Duck_t
{
    char name[MAX_CHARS_NAME_WITH_NUL];
} Duck_t;

#endif // DUCK_R
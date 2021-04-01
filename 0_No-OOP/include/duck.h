#ifndef DUCK_H
#define DUCK_H

#define MAX_CHARS_NAME 10

typedef struct Duck_t
{
    char name[MAX_CHARS_NAME];
} Duck_t;

Duck_t * duckCreate( void );
void duckInit( Duck_t * thisDuck, char * name );
void duckShow( Duck_t * thisDuck );
void duckDestroy( Duck_t * thisDuck );

#endif // DUCK_H
#ifndef DUCK_H
#define DUCK_H

#define MAX_CHARS_NAME 10
#define MAX_CHARS_NAME_WITH_NUL (MAX_CHARS_NAME+1)

typedef struct Duck_t * p_Duck_t;

void duckQuack( p_Duck_t thisDuck );
void duckShow( p_Duck_t thisDuck );
void duckDestroy( p_Duck_t thisDuck );

#endif // DUCK_H
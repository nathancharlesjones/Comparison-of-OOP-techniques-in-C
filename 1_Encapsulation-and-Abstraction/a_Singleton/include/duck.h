#ifndef DUCK_H
#define DUCK_H

#define MAX_CHARS_NAME 10
#define MAX_CHARS_NAME_WITH_NUL (MAX_CHARS_NAME+1)

void duckInit( char * name );
void duckShow( void );

#endif // DUCK_H
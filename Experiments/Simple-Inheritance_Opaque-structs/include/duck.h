#ifndef DUCK_H
#define DUCK_H

#define MAX_NUM_DUCK_OBJS 10
#define MAX_CHARS_NAME 10

void * duckCreate_dynamic( void );
void * duckCreate_static( void );
void duckInit( void * thisDuck, char * name );
char * duckGetName( void * thisDuck );
void duckShow( void * thisDuck );
void duckDeinit( void * thisDuck );
void duckDestroy_dynamic( void * thisDuck );
void duckDestroy_static( void * thisDuck );

#endif // DUCK_H
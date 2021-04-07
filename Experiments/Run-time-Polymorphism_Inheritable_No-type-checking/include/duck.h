#ifndef DUCK_H
#define DUCK_H

#define MAX_NUM_DUCK_OBJS 10

void * duckCreate_dynamic( char * name );
void * duckCreate_static( char * name );
void duckSetName( void * thisDuck, char * name );
char * duckGetName( void * thisDuck );
void duckQuack( void * thisDuck );
void duckShow( void *thisDuck );
void duckDestroy( void * thisDuck );

#endif // DUCK_H
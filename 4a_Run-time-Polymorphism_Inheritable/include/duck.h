#ifndef DUCK_H
#define DUCK_H

#include "duck.r"

#define MAX_NUM_DUCK_OBJS 10

typedef struct Duck_t * Duck;

Duck duckCreate_dynamic( char * name );
Duck duckCreate_static( char * name );
void duckSetName( Duck thisDuck, char * name );
char * duckGetName( Duck thisDuck );
void duckQuack( Duck thisDuck );
void duckShow( Duck thisDuck );
void duckDestroy( Duck thisDuck );

#endif // DUCK_H
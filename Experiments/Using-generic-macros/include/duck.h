#ifndef DUCK_H
#define DUCK_H

typedef struct Duck_t * Duck;

Duck duckCreate( void );
void duckInit( Duck thisDuck, char * name );

char * duckGetName( Duck thisDuck );
void duckQuack( Duck thisDuck );
void duckShow( Duck thisDuck );

#endif // DUCK_H
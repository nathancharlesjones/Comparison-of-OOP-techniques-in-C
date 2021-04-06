#ifndef DUCK_H
#define DUCK_H

typedef struct Duck_t * Duck;

Duck duckCreate( void );
void duckInit( Duck thisDuck, char * name );

char * _duckGetName( Duck thisDuck );
void _duckQuack( Duck thisDuck );
void _duckShow( Duck thisDuck );

#endif // DUCK_H
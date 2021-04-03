#ifndef DUCK_H
#define DUCK_H

void * duckCreate( void );
void duckInit( void * thisDuck, char * name );
void duckQuack( void * thisDuck );
void duckShow( void * thisDuck );

#endif // DUCK_H
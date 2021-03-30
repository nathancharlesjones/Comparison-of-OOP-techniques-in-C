#ifndef DUCK_H
#define DUCK_H

typedef struct Duck_t * Duck, Mallard;

Duck duckCreate( void );
void duckInit( Duck thisDuck, char * name );

void duckQuack( Duck thisDuck );
void duckShow( Duck thisDuck );

#endif // DUCK_H
#ifndef DUCK_H
#define DUCK_H

typedef struct Duck_t * Duck;

void duckSetName( Duck thisDuck, char * name );
char * duckGetName( Duck thisDuck );

void duckQuack( Duck thisDuck );
void duckShow( Duck thisDuck );
void duckDestroy( Duck thisDuck );

#endif // DUCK_H
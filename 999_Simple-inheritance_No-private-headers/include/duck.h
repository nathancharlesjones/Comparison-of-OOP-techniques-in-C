#ifndef DUCK_H
#define DUCK_H

// **NOT GOOD**: The value below is hand-calculated and may not result in proper alignment in memory
#define sizeof_Duck_t 10

typedef struct Duck_t * Duck;

Duck duckCreate( void );
void duckInit( Duck thisDuck, char * name );
void duckShow( Duck thisDuck );
char * duckGetName( Duck thisDuck );

#endif // DUCK_H
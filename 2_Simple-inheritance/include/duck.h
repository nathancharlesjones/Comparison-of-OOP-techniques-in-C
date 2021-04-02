#ifndef DUCK_H
#define DUCK_H

#define MAX_NUM_DUCK_OBJS 10

typedef struct Duck_t * Duck;

Duck duckCreate_dynamic( void );
Duck duckCreate_static( void );
void duckInit( Duck thisDuck, char * name );
void duckShow( Duck thisDuck );
void duckDeinit( Duck thisDuck );
void duckDestroy_dynamic( Duck thisDuck );
void duckDestroy_static( Duck thisDuck );

#endif // DUCK_H
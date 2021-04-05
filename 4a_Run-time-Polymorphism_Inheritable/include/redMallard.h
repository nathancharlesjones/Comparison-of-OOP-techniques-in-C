#ifndef RED_MALLARD_H
#define RED_MALLARD_H

#define MAX_NUM_MALLARD_OBJS 10

typedef struct redMallard_t * redMallard;

redMallard redMallardCreate_dynamic( void );
redMallard redMallardCreate_static( void );
void redMallardInit( redMallard thisRedMallard, char * name, featherColor color );
void redMallardShow( redMallard thisRedMallard );
void redMallardMigrate( redMallard thisRedMallard );
void redMallardeinit( redMallard thisRedMallard );
void redMallardDestroy_dynamic( redMallard thisRedMallard );
void redMallardDestroy_static( redMallard thisRedMallard );

#endif // RED_MALLARD_H
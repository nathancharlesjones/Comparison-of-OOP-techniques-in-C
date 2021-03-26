#ifndef RED_MALLARD_H
#define RED_MALLARD_H

typedef struct redMallard_t * redMallard;

redMallard redMallardCreate( void );
void redMallardInit( redMallard thisRedMallard, char * name, featherColor color );
void redMallardQuack( redMallard thisRedMallard );
void redMallardShow( redMallard thisRedMallard );

#endif // RED_MALLARD_H
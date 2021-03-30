#ifndef RED_MALLARD_H
#define RED_MALLARD_H

typedef struct redMallard_t * redMallard;

redMallard redMallardCreate( void );
void redMallardInit( redMallard thisRedMallard, char * name, featherColor color );

char * _redMallardGetName( redMallard thisRedMallard );
void _redMallardQuack( redMallard thisRedMallard );
void _redMallardShow( redMallard thisRedMallard );

const char * _redMallardGetColor( redMallard thisRedMallard );
void _redMallardMigrate( redMallard thisRedMallard );

#endif // RED_MALLARD_H
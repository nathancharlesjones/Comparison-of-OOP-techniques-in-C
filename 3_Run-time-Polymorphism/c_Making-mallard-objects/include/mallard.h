#ifndef MALLARD_H
#define MALLARD_H

typedef enum { WHITE, RED, BROWN } featherColor;

p_Duck_t mallardNew( char * name, featherColor color );

#endif // MALLARD_H
#ifndef RUBBER_H
#define RUBBER_H

typedef enum {SMALL, MEDIUM, LARGE} duck_size;

p_Duck_t rubberNew( char * name, duck_size size );

#endif // RUBBER_H
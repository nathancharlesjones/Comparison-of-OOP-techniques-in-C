# Encapsulation

## Description

The easiest OOP principle to introduce in C is "encapsulation". A software object that is "encapsulated" does not expose to other parts of the program how it is constructed. This prevents the rest of the program from reaching in and directly manipulating the object's attributes. In this example, the object "Duck_t" is encapsulated by virtue of the fact that it was moved from "duck.h" to "duck.c", which no other part of the program is privy to. Instead, only a pointer to this object is exposed, which the rest of the program can use to refer to "Duck" objects. Structs that don't expose their internal data elements to the rest of the program are sometimes called "opaque structs".

```
// include/duck.h
typedef struct Duck_t * Duck;
```

The rest of the program is able to interact with these "Duck" objects using the function prototypes defined in "duck.h". These functions are effectively the interface or public functions of all "Duck" objects.

```
// include/duck.h
Duck duckCreate_dynamic( void );
Duck duckCreate_static( void );
void duckInit( Duck thisDuck, char * name );
...
```

This is demonstrated in "main.c". First, "Duck" objects are created and initialized.

```
// source/main.c
Duck Huey = duckCreate_dynamic();
...
duckInit(Huey, "Huey");
```

Two "Create" functions are provided to demonstrate that _either_ dynamic or static memory allocation can be used in the implementation of these objects. The function `duckCreate_dynamic()` uses `malloc()` to dynamically allocate memory on the heap for each object. The function `duckCreate_static()` utilizes an array of "Duck" objects that is defined in `duck.c` and simply passes out pointers to the elements of this array. The array of "Duck" objects is allocated in static memory and, thus, might be useful to developers who want or need to avoid the use of heap memory. Actual projects will likely only need one implementation; both are shown here and for many of the projects simply for completeness.

After a `Duck` object has been created, the program can use the public functions ("duckShow") to interact with them.

```
// source/main.c
duckShow(Huey);
```

Notice how the program can't directly access the "name" field of the "Duck" objects like it could in the project "0_No-OOP". Although we've only just starting exploring OOP techniques in C, I want to note at this point that just this technique is sufficient to understand all of the techniques discussed in ["Design Patterns for Embedded Systems in C"](https://www.amazon.com/Design-Patterns-Embedded-Systems-Engineering/dp/1856177076) by Bruce Powel Douglass.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
// source/main.c
int
main( void )
{
    printf("|__Creating duck objects:\n");    -->    |__Creating duck objects:

    Duck Huey = duckCreate_dynamic();
    Duck Dewey = duckCreate_dynamic();
    Duck Louie = duckCreate_static();

    duckInit(Huey, "Huey");                   -->        Initializing new duck with name: Huey
    duckInit(Dewey, "Dewey");                 -->        Initializing new duck with name: Dewey
    duckInit(Louie, "Louie");                 -->        Initializing new duck with name: Louie

    printf("|__Showing duck objects:\n");     -->    |__Showing duck objects:
    
    duckShow(Huey);                           -->        Hi! My name is Huey.
    duckShow(Dewey);                          -->        Hi! My name is Dewey.
    duckShow(Louie);                          -->        Hi! My name is Louie.

    printf("|__Destroying duck objects:\n");  -->    |__Destroying duck objects:

    duckDestroy_dynamic(Huey);                -->        Destroying Duck object with name: Huey
    duckDestroy_dynamic(Dewey);               -->        Destroying Duck object with name: Dewey
    duckDestroy_static(Louie);                -->        Destroying Duck object with name: Louie

    return 0;
}
```

## References
- "Multiple-Instance Module" from "TDD for Embedded C", pg 225
    - [Code example](https://github.com/jwgrenning/tddec-code/blob/master/code/include/util/CircularBuffer.h)
- Miro Samek describes "encapsulation" in section 1 of his [PDF](https://www.state-machine.com/doc/AN_OOP_in_C.pdf) (code example [here](https://github.com/QuantumLeaps/OOP-in-C/tree/master/encapsulation)). At the risk of being very wrong, though, I'll state that I don't think we can call Miro's technique encapsulation since the struct definitions for the objects in question are placed in the public header file, allowing any other part of the program to access them.
- Axel Schreiner discusses encapsulation in ["OOP in ANSI C"](https://www.cs.rit.edu/~ats/books/ooc.pdf), Chapter 1, though he uses objects of type `void *` (which we'll discuss in Project 5a) and chooses needlessly convoluted examples (in my opinion).
    - [Code example](https://github.com/shichao-an/ooc/tree/master/01)
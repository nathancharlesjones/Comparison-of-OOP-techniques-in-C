# Encapsulation

## Description

The easiest OOP principle to introduce in C is "encapsulation". A software object that is "encapsulated" does not expose to other parts of the program how it is constructed. This prevents the rest of the program from reaching in and directly manipulating the object's attributes. In this example, the object "Duck_t" is encapsulated by virtue of the fact that it was moved from "duck.h" to "duck.c", which no other part of the program is privy to. Instead, only a pointer to this object is exposed, which the rest of the program can use to refer to "Duck" objects.

```
// include/duck.h
typedef struct Duck_t * Duck;
```

The rest of the program is able to interact with these "Duck" objects using the function prototypes defined in "duck.h". These functions are effectively the interface or public functions of all "Duck" objects.

```
// include/duck.h
Duck duckCreate( void );
void duckInit( Duck thisDuck, char * name );
void duckShow( Duck thisDuck );
```

This is demonstrated in "main.c". First, "Duck" objects are created and initialized.

```
// source/main.c
Duck Huey = duckCreate();
duckInit(Huey, "Huey");
```

Then, the program can use the public functions ("duckShow") to interact with the "Duck" objects.

```
// source/main.c
duckShow(Huey);
```

Notice how the program can't directly access the "name" field of the "Duck" objects like it could in the project "0_No-OOP".

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
|__Creating duck objects:
        Initializing new duck with name: Huey
        Initializing new duck with name: Duey
        Initializing new duck with name: Luey
|__Showing duck objects:
        Hi! My name is Huey.
        Hi! My name is Duey.
        Hi! My name is Luey.
```

## References
- "Multiple-Instance Module" from "TDD for Embedded C", pg 225
    - [Code example](https://github.com/jwgrenning/tddec-code/blob/master/code/include/util/CircularBuffer.h)
- Miro Samek describes "encapsulation" in section 1 of his [PDF](https://www.state-machine.com/doc/AN_OOP_in_C.pdf) (code example [here](https://github.com/QuantumLeaps/OOP-in-C/tree/master/encapsulation)). At the risk of being very wrong, though, I'll state that I don't think we can call Miro's technique encapsulation since the struct definitions for the objects in question are placed in the public header file, allowing any other part of the program to access them.
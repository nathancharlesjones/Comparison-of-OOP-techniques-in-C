# Simple Inheritance

## Description

Project 1b (["Composition with the Mediator Pattern"](https://github.com/nathancharlesjones/Comparison-of-OOP-techniques-in-C/tree/main/1b_Composition-with-the-Mediator-pattern)) introduced the idea that some objects have a HAS A relationship with other objects (e.g. "a car HAS AN engine") while some objects have an IS A relationship (e.g. "a swallow IS A bird"). This second relationship is called "inheritance", since a swallow "inherits" all of the aspects and functions of a generic "bird". Anything you would expect of a bird, you could expect of a swallow. We can simulate inheritance in C by taking advantage of a computer's memory layout.

In this project, we're going to create "duck" and "mallard" objects. Ducks do general duck things, like quack, and mallard do those things and more (in this case, they also migrate). Consider the memory layout of a "duck" object: it could have just about anything in it, but ours just has space for a name.

```
// include/duck.r
#define MAX_CHARS_NAME 10

typedef struct Duck_t
{
    char name[MAX_CHARS_NAME];
} Duck_t;
```

(The ".r" extension is meant to indicate a private header file, the reason for which will be explained a little later.) In memory, this struct might look like this:

```
|---------------|--------|---------|
|               |        | name[0] |
|               |        | name[1] |
|               |        | name[2] |
|               |        | name[3] |
| Duck_t object | name[] | name[4] |
|               |        | name[5] |
|               |        | name[6] |
|               |        | name[7] |
|               |        | name[8] |
|               |        | name[9] |
|---------------|--------|---------|
```

Notice now that the "mallard" objects have a Duck_t object as the first data element, after which come any other mallard-specific attributes.

```
// include/mallard.r
typedef struct Mallard_t
{
    Duck_t parentDuck;
    featherColor myColor;
} Mallard_t;
```

The placement of this Duck_t object is crucial! Consider the layout of a Mallard_t object in memory:

```
|------------------|---------------|--------|---------|
|                  |               |        | name[0] |
|                  |               |        | name[1] |
|                  |               |        | name[2] |
|                  |               |        | name[3] |
|                  | Duck_t object | name[] | name[4] |
| Mallard_t object |               |        | name[5] |
|                  |               |        | name[6] |
|                  |               |        | name[7] |
|                  |               |        | name[8] |
|                  |               |        | name[9] |
|                  |             featherColor         |
|------------------|---------------|--------|---------|
```

In this manner, a pointer to a Mallard_t object IS ALSO A pointer to a Duck_t object, since the starting address of both objects is the same. We can exploit this as shown in `main.c` by creating a Mallard_t object and doing both "duck" and "mallard" things with it (this requires a cast to "Duck" so that the compiler doesn't complain about mismatched types).

```
// source/main.c
duckShow((Duck)Bill);
```

The private header file is necessary so that derived classes, like "mallard.h", can see the full internals of the base class that they're inheriting from, but the rest of the program cannot (at least, not if they're behaving themselves). Unfortunately, the "duckShow()" function has no concept of "Mallard" or "featherColor", so they aren't able to be included in the sentence that gets printed. Additionally, we have no way for the "Mallard" class to add functions to an interface which _further_ derived classes could then inherit. We'll fix these problems in a future project.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
// source/main.c
int
main( void )
{    
    Duck George = duckCreate();
    Mallard Bill = mallardCreate();
    
    printf("|__Initializing mallard objects:\n");                    -->  |__Initializing mallard objects:

    duckInit(George, "George");                                      -->      Initializing duck with name: George
    mallardInit(Bill, "Bill", BROWN);                                -->      Initializing new mallard duck with name: Bill
                                                                              Initializing duck with name: Bill

    printf("|__Showing duck and mallard objects:\n");                -->  |__Showing duck and mallard objects:
    
    duckShow(George);                                                -->      Hi! My name is George.
    mallardShow(Bill);                                               -->      Hi! I'm a mallard duck. My name is Bill. I have brown feathers.
    
    printf("|__Showing mallard objects (cast to duck objects):\n");  -->  |__Showing mallard objects (cast to duck objects):
    
    duckShow((Duck)Bill);                                            -->      Hi! My name is Bill.

    return 0;
}
```

## References
- ["OOP in C", Section 2](https://www.state-machine.com/doc/AN_OOP_in_C.pdf), Miro Samek
    - [Code example](https://github.com/QuantumLeaps/OOP-in-C/tree/master/inheritance)
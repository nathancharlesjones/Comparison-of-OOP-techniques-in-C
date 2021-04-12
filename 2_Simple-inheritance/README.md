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
+---------------+--------+---------+
|               |        | name[0] |
|               |        +---------|
|               |        | name[1] |
|               |        +---------|
|               |        | name[2] |
|               |        +---------|
|               |        | name[3] |
|               |        +---------|
| Duck_t object | name[] | name[4] |
|               |        +---------|
|               |        | name[5] |
|               |        +---------|
|               |        | name[6] |
|               |        +---------|
|               |        | name[7] |
|               |        +---------|
|               |        | name[8] |
|               |        +---------|
|               |        | name[9] |
+---------------+--------+---------+
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
+------------------+---------------+--------+---------+
|                  |               |        | name[0] |
|                  |               |        +---------|
|                  |               |        | name[1] |
|                  |               |        +---------|
|                  |               |        | name[2] |
|                  |               |        +---------|
|                  |               |        | name[3] |
|                  |               |        +---------|
|                  | Duck_t object | name[] | name[4] |
| Mallard_t object |               |        +---------|
|                  |               |        | name[5] |
|                  |               |        +---------|
|                  |               |        | name[6] |
|                  |               |        +---------|
|                  |               |        | name[7] |
|                  |               |        +---------|
|                  |               |        | name[8] |
|                  |               |        +---------|
|                  |               |        | name[9] |
|                  +---------------+--------+---------|
|                  |            featherColor          |
+------------------+----------------------------------+
```

In this manner, a pointer to a Mallard_t object IS ALSO A pointer to a Duck_t object, since the starting address of both objects is the same. We can exploit this as shown in `main.c` by creating a Mallard_t object and doing both "duck" and "mallard" things with it (this requires a cast to "Duck" so that the compiler doesn't complain about mismatched types).

```
// source/main.c
duckShow((Duck)Bill);
```

The private header file is necessary so that derived classes, like "mallard.h", can see the full internals of the base class that they're inheriting from, but the rest of the program cannot (at least, not if they're behaving themselves). Unfortunately, the "duckShow()" function has no concept of "Mallard" or "featherColor", so they aren't able to be included in the sentence that gets printed and each derived class object must be explicitly cast to the base class for the project to compile cleanly. We'll fix these problems in future projects. The third group of projects, 3a/3b/3c, introduce the concept of polymorphism and allow for functions to "behave" differently when called on different types of objects, though not in a way that's inheritable; they work based on the assumption that the base class is an "abstract data type", whose implementation is fulfilled by one of many derived classes, with the layers of derived classes only going one level deep. The fourth project shows how to create inheritable classes that behave polymorphically, but still require the calling code to explicitly cast an object to different types. The fifth group of projects allows for both, in slightly different ways.

Additionally in this project, we're adding a "Deinit" function. This allows us to separate the part of the code that clears out the object in question from the part of the code that frees the pointer to the object. Some objects, such as motor controllers, may require very specific deinitialization (such as to ensure the they are off or in a home position) but we only need to free the pointer to the obejct in ONE location. So we now required that objects be deinitialized prior to destorying them and it is incumbent upon the derived classes to make sure that their base class is deinitialized at the same time they are.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
// source/main.c
int
main( void )
{    
    printf("|__Creating duck and mallard objects\n");                -->  |__Creating duck and mallard objects
    
    Duck George = duckCreate_static();
    Mallard Bill = mallardCreate_dynamic();
    
    printf("|__Initializing mallard objects:\n");                    -->  |__Initializing mallard objects:

    duckInit(George, "George");                                      -->      Initializing duck with name: George
    mallardInit(Bill, "Bill", BROWN);                                -->      Initializing new mallard duck with name: Bill
                                                                              Initializing duck with name: Bill

    printf("|__Showing duck and mallard objects:\n");                -->  |__Showing duck and mallard objects:
    
    duckShow(George);                                                -->      Hi! My name is George.
    mallardShow(Bill);                                               -->      Hi! I'm a mallard duck. My name is Bill. I have brown feathers.
    
    printf("|__Showing mallard objects (cast to duck objects):\n");  -->  |__Showing mallard objects (cast to duck objects):
    
    duckShow((Duck)Bill);                                            -->      Hi! My name is Bill.

    printf("|__Deinitializing duck and mallard objects:\n");         -->  |__Deinitializing duck and mallard objects

    duckDeinit(George);                                              -->      Deinitializing Duck object with name: George
    mallardDeinit(Bill);                                             -->      Deinitializing Mallard object with name: Bill
                                                                              Deinitializing Duck object with name: Bill

    printf("|__Destroying duck and mallard objects:\n");             -->  |__Destroying duck and mallard objects:
    
    duckDestroy_static(George);
    mallardDestroy_dynamic(Bill);

    return 0;
}
```

## References
- ["OOP in C", Section 2](https://www.state-machine.com/doc/AN_OOP_in_C.pdf), Miro Samek
    - [Code example](https://github.com/QuantumLeaps/OOP-in-C/tree/master/inheritance)
- Axel Schreiner discusses the idea of object inheritance in ["OOP in ANSI C"](https://www.cs.rit.edu/~ats/books/ooc.pdf), Chapter 4, though at that point in the book he's already discussed the idea of vtables (which we'll get to next), so it might more sense after Project 3c.
    - [Code example](https://github.com/shichao-an/ooc/tree/master/04)
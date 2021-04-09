# Run-time Polymorphism (Inheritable, No casting)

## Description

Project 4 provided a solution to achieve full inheritance at the cost of having to explicitly cast objects to different types based on the functions being called. Near as I can tell, there isn't a way to direct the C compiler to treat two or more data types as being equivalent (in the sense that a `Mallard` IS A `Duck` so a function with an input parameter of `Duck` should also accept `Mallard`). However, there IS a way to treat a data type as a "non type": casting it to `void *`. `void *`, a pointer to void, is basically a "pointer to nothing" or, perhaps more accurately, a "pointer to anything". (The keyword `void`, used for functions that take no arguments or return no values, is similar in the sense that we're not referring to a particular data type, but it isn't exactly the same. The C compiler won't let you create a variable of type `void` for instance, but a variable of type `void *` is perfectly valid.) If a function lists a void pointer as an input parameter, that function can, effectively receive a pointer to any data type.

If you're thinking, "Sweet! All we need to do is change all of our `Duck`, `Mallard`, and `redMallard` objects to `void *` and we're done!", you'd be right! Sort of. Making [that change _does_ work](https://github.com/nathancharlesjones/Comparison-of-OOP-techniques-in-C/tree/main/Experiments/Run-time-Polymorphism_Inheritable_No-type-checking), but at the cost of completely circumventing the built-in type-checking that the C compiler was doing in the first place to prevent us from being able to use our polymorphic functions without explicit casts. This has serious implications for, at least, program stability, if not also safety or security: if we change our functions to, quite literally, accept any argument and then modify memory values at that location or treat the values as function pointers (since our objects _do_ have a vtable with a list of function pointers that we are executing), then any mistake in calling a function with a different object or a pointer to something else entirely could result in a system-halting error (at best) or an error that creates a security vulnerability or safety hazard (at worst). I think, if we're to make this change, we need to add in our own type-checking in some form or fashion. This project does just that.

We'll start by building off of the interface variables from Project 3c (e.g. `duckFromHeapMem`, `mallardFromStaticMem`, etc). Those variables pointed to the exact interfaces (i.e. list of functions) that defined each type of object and was used by the `duckCreate()` function in order to create and initialize the desired object (a.k.a. the Factory pattern). Testing to see if an object's vtable points to a specific interface is sufficient to tell if an object is of that type. For example, every `Mallard` object has, as it's first data element, a pointer to either `mallardFromHeapMem` or `mallardFromStaticMem`. So if our input argument, which is of type `void *`, _also_ happens to have, as it's first data element, a pointer to either `mallardFromHeapMem` or `mallardFromStaticMem`, then we can be reasonably confident that this object of type `void *` is actually of type `Mallard`.

You can see this added to our project in the form of a helper function, `objIsDuck()` (also, `objIsMallard()` and `objIsRedMallard()`, one for each class). Every `Duck` function first asserts that the input argument is a `Duck` by testing if it points to a `Duck` interface. `objIsDuck()` checks if our `void *` object happens to have a pointer to either `duckFromHeapMem` or `duckFromStaticMem`, which would make it a `Duck` object (and it also checks if the object in question is derived from the `Duck` class; more on that later).

```
// source/duck.c
bool
objIsDuck( void * thisDuck )
{
    bool ret = false;
    ...
    void const * thisType = *(Duck_Interface *)thisDuck;

    if( ( thisType == duckFromHeapMem ) || ( thisType == duckFromStaticMem ) || parentIsDuck(thisType) ) ret = true;

    return ret;
}

void
duckSetName( void * thisDuck, char * name )
{
    ...
    ASSERT(objIsDuck(thisDuck));
    ...
}

void
duckQuack( void * thisDuck )
{
    ...
    ASSERT(objIsDuck(thisDuck));
    ...
}

...etc
```

So what happens if the object is of type `Mallard`? We want derived objects to also pass the "is duck" test. They don't point to a `Duck` interface, though, so we'll need to figure out a way for them to hold information about the fact that they're derived froms the `Duck` class. After a bit of trial and error, I decided on adding a function to the Duck interface called `getParentInterface()`, which returns the interface of the base class from which the current class is derived. Objects of type `redMallard` return a pointer to one of the `Mallard` interfaces, `Mallard` objects return a pointer to one of the `Duck` interfaces, and `Duck` objects return `NULL` (since they sit at the top of the class hierarchy and have no base class). Thus, we can traverse an object's entire chain of parent classes by repeatedly calling the `getParentInterface()` on each new interface. In this manner, we can say that an object is of type `Duck` if either IT points to a `Duck` interface OR if it's parent interface points to a `Duck` interface (or the parent's parent interface is a `Duck`, or the parent's parent's parent interface is a `Duck`, or... ). 

```
bool
typeIsDuck( void * thisType )
{
    bool ret = false;

    while( thisType && thisType != duckFromHeapMem && thisType != duckFromStaticMem )
    {
        thisType = ((Duck_Interface)thisType)->getParentInterface();
    }

    if( ( thisType == duckFromHeapMem ) || ( thisType == duckFromStaticMem ) ) ret = true;

    return ret;
}

bool
parentIsDuck( void * thisType )
{
    return typeIsDuck(thisType);
}
```

Let's pause and inspect what this all looks like in memory. An object of type `Duck` looks like this:

```
+--------+------------------+                    +----------------------+---------------------+             +------+
|        |     vtable       |  +-------------->  |                      | *getParentInterface | +---------> | NULL |
|        +--------+---------+  vtable points to  |                      +---------------------+ Fcn returns +------+
|        |        | name[0] |  a Duck_Interface_ | Duck_Interface_      | *create             | NULL
|        |        +---------+  Struct object     | Struct object        +---------------------+
|        |        | name[1] |                    |                      | *destroy            |
|        |        +---------+                    | e.g. duckFromHeapMem +---------------------+
|        |        | name[2] |                    |                      | *show               |
|        |        +---------+                    +----------------------+---------------------+
|        |        | name[3] |
|        |        +---------+
| Duck_t | name[] | name[4] |
| obj    |        +---------+
|        |        | name[5] |
|        |        +---------+
|        |        | name[6] |
|        |        +---------+
|        |        | name[7] |
|        |        +---------+
|        |        | name[8] |
|        |        +---------+
|        |        | name[9] |
+--------+--------+---------+
```

An object of type `Mallard` looks like this:

```
                                                                                   Fcn returns pointer to Duck interface
                                                                                  +----------------------------------------------------v
+-----------+--------+------------------+                    +------------+-------------------------------------------------+   +----------------------+---------------------+             +------+
|           |        |     vtable       |  +-------------->  |            | *getParentInterface |                           |   |                      | *getParentInterface | +---------> | NULL |
|           |        +--------+---------+  vtable points to  | Duck_      +---------------------+                           |   |                      +---------------------+ Fcn returns +------+
|           |        |        | name[0] |  a Duck_Interface_ | Interface_ | *create             |                           |   | Duck_Interface_      | *create             | NULL
|           |        |        +---------+  Struct object     | Struct obj +---------------------+ Mallard_Interface_Struct  |   | Struct object        +---------------------+
|           |        |        | name[1] |                    |            | *destroy            | object                    |   |                      | *destroy            |
|           |        |        +---------+                    |            +---------------------+                           |   | e.g. duckFromHeapMem +---------------------+
|           |        |        | name[2] |                    |            | *show               | e.g. mallardFromStaticMem |   |                      | *show               |
|           |        |        +---------+                    +------------+---------------------+                           |   +----------------------+---------------------+
|           |        |        | name[3] |                    |              *migrate            |                           |
|           |        |        +---------+                    +----------------------------------+---------------------------+
| Mallard_t | Duck_t | name[] | name[4] |
| obj       | obj    |        +---------+
|           |        |        | name[5] |
|           |        |        +---------+
|           |        |        | name[6] |
|           |        |        +---------+
|           |        |        | name[7] |
|           |        |        +---------+
|           |        |        | name[8] |
|           |        |        +---------+
|           |        |        | name[9] |
|           +--------+--------+---------+
|           |       featherColor        |
+-----------+---------------------------+
```

In this manner, the objects of all derived classes point the way up through their individual class hierarchy.

**IT'S REALLY IMPORTANT TO NOTE** that although we've implemented a basic form of type-checking at this point, our framework still isn't completely safe from garbage arguments causing it to run off the rails. In following the chain of `getParentInterfaces()`, we're still assuming that the `void *` object being passed to a function actually implements the `getParentInterface()` function. In essence, if we call a `Duck` method on something that is not an object of any type (e.g. it is a pointer to an integer), it will fail the test of whether it points to a pointer to a `Duck` interface (`if( ( thisType == duckFromHeapMem ) || ( thisType == duckFromStaticMem )...`) and then our framework will **assume** that the first memory value of the interface is a function pointer (to a function that _should_ return the memory address of the parent interface) and then **jump to that location and start executing code**. This is a huge flaw, mitigated only by the thought that calling a class function on something that isn't an object (of that or any other class) shouldn't ever really happen.

The last change to note is that each classes' `init()` and `deinit()` have been put back in their private header files. It's possible to put them in the base class interface, but referencing them from their was a bit convoluted and also unnecessary. Since each class already knows which `init()`/`deinit()` functions to call, there isn't really a need to put them into the interface.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
int
main( void )
{
    printf("|__Creating duck object\n");                                             +->  |__Creating duck object

    void * George = duckCreate(duckFromHeapMem, "George");                           +->      Initializing duck with name: George

    void * Bill = duckCreate(mallardFromStaticMem, "Bill", BROWN);                   +->      Initializing duck with name: Bill
                                                                                              Initializing new mallard duck with name: Bill
    void * Mary = duckCreate(redMallardFromStaticMem, "Mary", RED);                  +->      Initializing duck with name: Mary
                                                                                              Initializing new mallard duck with name: Mary
                                                                                              Initializing new red-breasted mallard with name: Mary

    printf("|__Quacking duck and mallard objects:\n");                               +->  |__Quacking duck and mallard objects:

    duckQuack(George);                                                               +->      George: Quack!
    duckQuack(Bill);                                                                 |->      Bill: Quack!
    duckQuack(Mary);                                                                 +->      Mary: Quack!

    printf("|__Showing duck and mallard objects:\n");                                +->  |__Showing duck and mallard objects:

    duckShow(George);                                                                +->      Hi! My name is George.
    duckShow(Bill);                                                                  |->      Hi! I'm a mallard duck. My name is Bill. I have brown feathers.
    duckShow(Mary);                                                                  +->      Hi! I'm a red-breasted mallard duck. My name is Mary. I have red feathers.

    printf("|__Migrating mallard objects:\n");                                       +->  |__Migrating mallard objects:

    mallardMigrate(Bill);                                                            +->      Bill: I'm migrating!
    mallardMigrate(Mary);                                                            +->      Mary: I'm migrating from North to South America with my fellow red-breasted mallards!

    printf("|__Destroying duck and mallard objects:\n");                             +->  |__Destroying duck and mallard objects:

    duckDestroy(George);                                                             +->      Deinitializing duck object with name: George
    duckDestroy(Bill);                                                               +->      Deinitializing Mallard object with name: Bill
                                                                                              Deinitializing duck object with name: Bill
    duckDestroy(Mary);                                                               +->      Deinitializing Red Mallard object with name: Mary
                                                                                              Deinitializing Mallard object with name: Mary
                                                                                              Deinitializing duck object with name: Mary

    printf("|__Testing 'type-checking' (calling Mallard method on Duck object):\n")  +->  |__Intentionally calling mallard functions on duck objects (to test the 'type-checking'):

    void * Helen = duckCreate(duckFromHeapMem, "Helen");                             +->      Initializing duck with name: Helen
    mallardMigrate(Helen);                                                           +->  ERROR: Assert failed in source/mallard.c at line 145

    return 0;
}
```

## References
- None that weren't already listed for other projects (I made up most of this by myself!), though I did get the idea for `void *` object types from ["OOP in ANSI C"](https://www.cs.rit.edu/~ats/books/ooc.pdf) by Axel Schreiner.
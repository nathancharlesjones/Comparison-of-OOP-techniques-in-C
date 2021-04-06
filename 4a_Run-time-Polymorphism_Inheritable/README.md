# Run-time Polymorphism (Inheritable)

## Description

While the second project introduced the concept of simple inheritance (the idea that if I embed a base class object as the first element to a derived class object, then a pointer to the derived class _is also_ a pointer to the base class portion of that object), it also introduced two problems with that simplified approach:

1. each class still only operated on it's own data type, requiring explicit casts to other data types when calling base class methods (e.g. `duckShow((Duck)myMallard))`), and
2. the base class methods had no concept of any of the derived classes so they couldn't really behave polymorphically (e.g. `duckShow((Duck)myMallard))` only showed the `Duck` message, not the `Mallard` message).

Projects 3a/3b/3c solved these two problems, but only by restricting the base class to an "abstract data type", whose implementation was fulfilled by one of many derived classes, with the layers of derived classes only going one level deep. In this project, we're going to backtrack a bit on our solution in order to create a framework that's truly inheritable. The final result will still behave polymorphically, but it go back to requiring explicit casts. Solving both problems at the same time will be left to Project 5.

Consider the memory layout of the `Duck_t` object from Project 2 again.

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
+---------------+--------+---------|
```

In project 3a, we added the conept of a "vtable" to allow derived classes the ability to override certain base class functions. A pointer to this vtable was situated as the first element of our base class objects.

```
+---------------+------------------+                    +-----------------+----------+
|               |     vtable       |  +-------------->  |                 | *show    |
|               +--------+---------+  vtable points to  | Duck_Interface_ +----------+
|               |        | name[0] |  a Duck_Interface_ | Struct object   | *deinit  |
|               |        +---------+  Struct object     |                 +----------+
|               |        | name[1] |                    |                 | *destroy |
|               |        +---------+                    +-----------------+----------+
|               |        | name[2] |
|               |        +---------+
|               |        | name[3] |
|               |        +---------+
| Duck_t object | name[] | name[4] |
|               |        +---------+
|               |        | name[5] |
|               |        +---------+
|               |        | name[6] |
|               |        +---------+
|               |        | name[7] |
|               |        +---------+
|               |        | name[8] |
|               |        +---------+
|               |        | name[9] |
+---------------+------------------+
```

We then created a derived class, `Mallard`, that "inherited" from the base class, `Duck`.

```
+------------------+---------------+------------------+                    +-----------------+----------+
|                  |               |     vtable       |  +-------------->  |                 | *show    |
|                  |               +--------+---------+  vtable points to  | Duck_Interface_ +----------+
|                  |               |        | name[0] |  a Duck_Interface_ | Struct object   | *deinit  |
|                  |               |        +---------+  Struct object     |                 +----------+
|                  |               |        | name[1] |                    |                 | *destroy |
|                  |               |        +---------+                    +-----------------+----------+
|                  |               |        | name[2] |
|                  |               |        +---------+
|                  |               |        | name[3] |
|                  |               |        +---------+
|                  | Duck_t object | name[] | name[4] |
| Mallard_t object |               |        +---------+
|                  |               |        | name[5] |
|                  |               |        +---------+
|                  |               |        | name[6] |
|                  |               |        +---------+
|                  |               |        | name[7] |
|                  |               |        +---------+
|                  |               |        | name[8] |
|                  |               |        +---------+
|                  |               |        | name[9] |
|                  +---------------+--------+---------+
|                  |            featherColor          |
+------------------+----------------------------------+
```

Thus, a pointer to `Mallard_t` was also a pointer to `Duck_t` since they were overlaid on top of each other. In order to make the `Duck_Interface`, were going to do the same thing: embed the Duck_Interface_Struct in a new data type called "Mallard_Interface_Struct".

```
// include/mallard.r
typedef struct Mallard_Interface_Struct const * Mallard_Interface;

typedef struct Mallard_Interface_Struct
{
    Duck_Interface_Struct duckInterface;
    void (*migrate)( Mallard_t * thisMallard );
} Mallard_Interface_Struct;
```

Now our memory layout for a `Mallard` object looks like this:

```
+------------------+---------------+------------------+                    +-----------------+----------+--------------------+
|                  |               |     vtable       |  +-------------->  |                 | *show    |                    |
|                  |               +--------+---------+                    | Duck_Interface_ +----------+                    |
|                  |               |        | name[0] |  vtable points to  | Struct object   | *deinit  | Mallard_Interface_ |
|                  |               |        +---------+  a Duck_Interface_ |                 +----------+ Struct object      |
|                  |               |        | name[1] |  Struct object     |                 | *destroy |                    |
|                  |               |        +---------+                    +-----------------+----------+                    |
|                  |               |        | name[2] |                    |           *migrate         |                    |
|                  |               |        +---------+                    +----------------------------+--------------------+
|                  |               |        | name[3] |
|                  |               |        +---------+
|                  | Duck_t object | name[] | name[4] |
| Mallard_t object |               |        +---------+
|                  |               |        | name[5] |
|                  |               |        +---------+
|                  |               |        | name[6] |
|                  |               |        +---------+
|                  |               |        | name[7] |
|                  |               |        +---------+
|                  |               |        | name[8] |
|                  |               |        +---------+
|                  |               |        | name[9] |
|                  +---------------+--------+---------+
|                  |            featherColor          |
+------------------+----------------------------------+
```

By selectively casting `vtable` to the correct data type (e.g. casting to `Duck_Interface` to call the `show()`, `deinit()`, and `destroy()` functions and casting to `Mallard_Interface` to call the `migrate()` function), we can create a hierarchy of objects with limitless levels of inheritance.

Although the code for Project 3a was used as a base for this project, a few other changes have been made in order for this to work.

First, derived classes no longer return objects of the base class type. This worked well for the ADTs, since there was only ever going to be a single level of derived classes and they all were supposed to act like objects of the base class; the function `mallardCreate_dynamic()` could return an object of type `Duck` since it was only ever supposed to be an implementation of the `Duck` base class. However, in our current project, we may have an unlimited number of derived classes and making them all of a single type doesn't fully eliminate the need to explicit cast that object to another type if we're calling functions from various levels of our class hierarchy.

```
// include/mallard.h  <---- FROM PROJECT 3a
Duck mallardCreate_dynamic( char * name, featherColor color );

// include/mallard.h  <---- FROM PROJECT 4
Mallard mallardCreate_dynamic( char * name, featherColor color );
```

Similarly, all of the derived classes functions that override the base class functions have to match it's function signature (sometimes requiring us to downcast the input parameter to the derived class inside the function in order to access attributes of the derived class) but newly implemented functions operate on objects of the derived class.

```
// source/mallard.c
static void
mallardShow( Duck thisDuck )
{
    Mallard thisMallard = (Mallard)thisDuck;
    ...
}

void
mallardMigrate( Mallard thisMallard )
{
    ...
}
```

Second, every class needs to have some type of "init" and "deinit" functions declared in the private header file. This is because derived classes are responsible for allocating the memory space for their objects but they have to call their base class's `init()` function before completing their own initialization (since their attributes may require valid attributes from the base class). Every initialization function works this way: call the `init()` function for _its_ base class and then initialize its own attributes. For example, when an object of type `redMallard` is created:

1. `redMallardCreate_XXX()` handles the memory allocation and then calls `redMallardInit()`,
2. which calls `mallardInit()`,
3. which calls `duckInit()`.
4. `duckInit()` sets the object's name and returns to `mallardInit()`.
5. `mallardInit()` sets the object's `featherColor` and then returns to `redMallardInit()`,
6. which does nothing (at the moment).

I'm not a fan of declaring functions in the private header files (I'm not a huge fan of the private header files in the first place<sup>1</sup>), but this is the best way of communicating to future developers that the `init()` and `deinit()` functions are only to be called by derived classes, not by the code that uses the objects in question.

### Notes

1. The private header files serve their purpose, but they rely on developers respecting their intent and not peeking on the implementation details of each of the classes. Nothing other than propriety or discipline is preventing them from modifying each object directly after discerning from the private header files how each object is laid out in memory. Unfortunately, however, I could not come up with a way to implement any of the OOP techniques after Projects 1a/1b/1c without them (save for [this project](https://github.com/nathancharlesjones/Comparison-of-OOP-techniques-in-C/tree/main/Experiments/Using-generic-macros) in the "Experiments" folder, but that has its own downsides).

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
int
main( void )
{
    printf("|__Creating duck and mallard objects:\n");          +->  |__Creating duck and mallard objects:

    Duck George = duckCreate_dynamic("George");                 +->      Initializing duck object with name: George
    Mallard Bill = mallardCreate_static("Bill", BROWN);         +->      Initializing duck object with name: Bill
                                                                         Initializing mallard duck with name: Bill
    redMallard Mary = redMallardCreate_dynamic("Mary", WHITE);  +->      Initializing duck object with name: Mary
                                                                         Initializing mallard duck with name: Mary
                                                                         Initializing red-breasted mallard with name: Mary

    printf("|__Quacking duck and mallard objects:\n");          +->  |__Quacking duck and mallard objects:

    duckQuack(George);                                          +->      George: Quack!
    duckQuack((Duck)Bill);                                      |->      Bill: Quack!
    duckQuack((Duck)Mary);                                      +->      Mary: Quack!

    printf("|__Showing duck and mallard objects:\n");           +->  |__Showing duck and mallard objects:

    duckShow(George);                                           +->      Hi! My name is George.
    duckShow((Duck)Bill);                                       |->      Hi! I'm a mallard duck. My name is Bill. I have brown feathers.
    duckShow((Duck)Mary);                                       +->      Hi! I'm a red-breasted mallard duck. My name is Mary. I have white feathers.

    printf("|__Migrating mallard objects:\n");                  +->  |__Migrating mallard objects:

    mallardMigrate(Bill);                                       +->      Bill: I'm migrating!
    mallardMigrate((Mallard)Mary);                              +->      Mary: I'm migrating from North to South America with my fellow red-breasted mallards!

    printf("|__Destroying duck and mallard objects\n");         +->  |__Destroying duck and mallard objects

    duckDestroy(George);                                        +->      Deinitializing duck object with name: George
    duckDestroy((Duck)Bill);                                    +->      Deinitializing mallard object with name: Bill
                                                                         Deinitializing duck object with name: Bill
    duckDestroy((Duck)Mary);                                    +->      Deinitializing red mallard object with name: Mary
                                                                         Deinitializing mallard object with name: Mary
    return 0;                                                            Deinitializing duck object with name: Mary
}
```

## References
- None specific to this project, though the [references for Project 2](https://github.com/nathancharlesjones/Comparison-of-OOP-techniques-in-C/tree/main/2_Simple-inheritance#references) discuss the idea of "inheriting" an object by placing it as the first data element in another object.
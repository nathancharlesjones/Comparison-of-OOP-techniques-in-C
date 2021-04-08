# Run-time Polymorphism (Inheritable, No casting)

## Description

Project 4 provided a solution to achieve full inheritance at the cost of having to explicitly cast objects to different types based on the functions being called. Near as I can tell, there isn't a way to direct the C compiler to treat two or more data types as being equivalent (in the sense that a "Mallard" IS A "Duck" so a function with an input parameter of "Duck" should also accept "Mallard"). However, there IS a way to treat a data type as a "non type": casting it to "void *". "void *", a pointer to void, is basically a "pointer to nothing" or, perhaps more accurately, a "pointer to anything". (The keyword "void", used for functions that take no arguments or return no values, is similar in the sense that we're not referring to a particular data type, but it isn't exactly the same. The C compiler won't let you create a variable of type "void" for instance, but a variable of type "void *" is perfectly valid.) If a function lists a void pointer as an input parameter, that function can, effectively receive a pointer to any data type.

If you're thinking, "Sweet! All we need to do is change all of our 'Duck', 'Mallard', and 'redMallard' objects to 'void *' and we're done!", you'd be right! Sort of. Making [that change _does_ work](https://github.com/nathancharlesjones/Comparison-of-OOP-techniques-in-C/tree/main/Experiments/Run-time-Polymorphism_Inheritable_No-type-checking), but at the cost of completely circumventing the built-in type-checking that the C compiler was doing in the first place to prevent us from being able to use our polymorphic functions without explicit casts. This has serious implications for, at least, program stability, if not also safety or security: if we change our functions to, quite literally, accept any argument and then modify memory values at that location or treat the values as function pointers (since our objects _do_ have a vtable with a list of function pointers that we are executing), then any mistake in calling a function with a different object or a pointer to something else entirely could result in a system-halting error (at best) or an error that creates a security vulnerability or safety hazard (at worst). I think, if we're to make this change, we need to add in our own type-checking in some form or fashion. This project does just that.

We'll start by building off of the interface variables from Project 3c (e.g. `duckFromHeapMem`, `mallardFromStaticMem`, etc). Those variables pointed to the exact interfaces (i.e. list of functions) that defined each type of object and was used by the single "Create" function in order to create and initialize the desired object. Testing to see if an object's vtable points to a specific interface is sufficient to tell if an object is of that type. For example, every `Mallard` object has, as it's first data element, a pointer to either `mallardFromHeapMem` or `mallardFromStaticMem`. So if our input argument, which is of type `void *`, _also_ happens to have, as it's first data element, a pointer to either `mallardFromHeapMem` or `mallardFromStaticMem`, then we can be reasonably confident that this object of type `void *` is actually of type `Mallard`.

You can see this added to our project in the form of a helper function, `objIsDuck()`, which is used with an `ASSERT` macro. Every `Duck` function first asserts that the input argument is a `Duck` by testing if it points to a `Duck` interface.

```

```

- BaseClass and getParentInterface
- objIsDuck / parentIsDuck / typeIsDuck
- change all public objects to void *
- Add "init"/"deinit" function declarations to private header file

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

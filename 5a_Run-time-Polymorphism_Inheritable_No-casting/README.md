# Run-time Polymorphism (Inheritable, No casting)

## Description



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

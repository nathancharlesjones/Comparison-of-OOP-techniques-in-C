# Singleton

Encapsulation and abstraction are very similar concepts. Abstraction is the idea that the data in a class or module doesn't have a format with which a programmer can interact directly. A module that is abstracted could change it's specific implementation (e.g. the data types used to store certain values or the way certain functions are written) and the code that uses the module wouldn't have to change. Encapsulation is the idea that methods/functions that operate on data are put near the place where that data is defined. A module is well encapsulated if there aren't any functions in other modules that are needed to make it work.

This project demonstrates abstraction by declaring a `Duck_t` data type, which includes all of the data elements that are pertinent to creating and using a "duck" object, though the exact nature of these data types isn't revealed. It also demonstrates encapsulation by putting the functions that operate on `Duck_t` structs in `duck.h` and `duck.c`.

## Expected output

```
// source/main.c
int
main( void )
{
    printf("|__Creating duck objects:\n");                                    -->  |__Creating duck objects:

    Duck_t * Huey = duckCreate();
    Duck_t * Dewey = duckCreate();
    Duck_t * Louie = duckCreate();

    duckInit(Huey, "Huey");                                                   -->      Initializing new duck with name: Huey
    duckInit(Dewey, "Dewey");                                                 -->      Initializing new duck with name: Duey
    duckInit(Louie, "Louie");                                                 -->      Initializing new duck with name: Luey

    printf("|__Showing duck objects:\n");                                     -->  |__Showing duck objects:
    
    duckShow(Huey);                                                           -->      Hi! My name is Huey.
    duckShow(Dewey);                                                          -->      Hi! My name is Duey.
    duckShow(Louie);                                                          -->      Hi! My name is Luey.

    printf("|__Printing duck objects by directly accessing their names:\n");  -->  |__Printing duck objects by directly accessing their names:
    
    printf("\tAccessing name directly for: %s\n", Huey->name);                -->      Accessing name directly for: Huey
    printf("\tAccessing name directly for: %s\n", Dewey->name);               -->      Accessing name directly for: Dewey
    printf("\tAccessing name directly for: %s\n", Louie->name);               -->      Accessing name directly for: Louie

    printf("|__Destroying duck objects:\n");                                  -->  |__Destroying duck objects:

    duckDestroy(Huey);                                                        -->      Destroying Duck object with name: Huey
    duckDestroy(Dewey);                                                       -->      Destroying Duck object with name: Dewey
    duckDestroy(Louie);                                                       -->      Destroying Duck object with name: Louie

    return 0;
}
```

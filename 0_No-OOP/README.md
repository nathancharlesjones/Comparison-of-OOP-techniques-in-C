# No OOP

This project demonstrates no OOP techniques. All of the project's code lives in `main.c` and it's not written in a way to support any of the four principles of object-oriented programming (encapsulation, abstraction, polymorphism, and inheritance).

## Expected output

```
// source/main.c
int
main( void )
{
    printf("|__Creating duck objects:\n");                                    -->  |__Creating duck objects:

    Duck_t * Huey = duckNew("Huey");                                          -->      Initializing new duck with name: Huey
    Duck_t * Dewey = duckNew("Dewey");                                        -->      Initializing new duck with name: Duey
    Duck_t * Louie = duckNew("Louie");                                        -->      Initializing new duck with name: Luey

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

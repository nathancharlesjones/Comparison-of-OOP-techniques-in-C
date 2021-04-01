# No OOP

Used as a baseline against which to compare the other projects. This project uses no OOP techniques.

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
    duckInit(Dewey, "Duey");                                                  -->      Initializing new duck with name: Duey
    duckInit(Louie, "Luey");                                                  -->      Initializing new duck with name: Luey

    printf("|__Showing duck objects:\n");                                     -->  |__Showing duck objects:
    
    duckShow(Huey);                                                           -->      Hi! My name is Huey.
    duckShow(Dewey);                                                          -->      Hi! My name is Duey.
    duckShow(Louie);                                                          -->      Hi! My name is Luey.

    printf("|__Printing duck objects by directly accessing their names:\n");  -->  |__Printing duck objects by directly accessing their names:
    
    printf("\tAccessing name directly for: %s\n", Huey->name);                -->      Accessing name directly for: Huey
    printf("\tAccessing name directly for: %s\n", Dewey->name);               -->      Accessing name directly for: Duey
    printf("\tAccessing name directly for: %s\n", Louie->name);               -->      Accessing name directly for: Luey

    return 0;
}
```

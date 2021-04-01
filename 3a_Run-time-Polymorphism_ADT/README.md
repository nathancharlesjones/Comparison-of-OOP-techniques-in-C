# Run-time Polymorphism (ADT)

## Description

In our last project, ["Simple Inheritance"](https://github.com/nathancharlesjones/Comparison-of-OOP-techniques-in-C/tree/main/2_Simple-inheritance), although our base class functions could be called using our derived class ("Mallard"), the object had to be explicitly cast to the base class and the function could not access any of the data elements in the derived class.

```
// 2_Simple-inheritance/source/main.c

// "Bill" is a Mallard object, but is here treated
// exactly as though it were just a Duck object. The
// expected output is "Hi! My name is Bill." just as
// if Bill were a duck.
//
duckShow((Duck)Bill);
```

Ideally, we would be able to provide any derived object to any base class function without casting AND let the derived class define a function which _supercedes_ the base class's function. In other words, instead of writing `duckShow((Duck)Bill)` and seeing `"Hi! My name is Bill."` on the output, we'd like to write `duckShow(Bill)` (notice: no casting to type Duck) and see something like `"Hi! I'm a mallard duck. My name is Bill. I have brown feathers."` on the output. In this project, we're going to look at one way of doing this.

To do this, we first need to define a table of function pointers for each data type. This will allow derived classes the ability to change the default function for a base class to one that's specific to the derived class. Our Duck object will have one function, `duckShow()`, which we will allow derived classes to change and one function, `duckQuack()`, which we will not. Thus, `duckShow()` is the only only included in our interface definition. In C++ parlance, this is a "vtable" or "table of virtual functions" (the "virtual" part means that they are intended to be defined by the derived classes).

```
// include/duck.r
typedef struct Duck_Interface_Struct * Duck_Interface;
...
typedef struct Duck_Interface_Struct
{
    void (*show)( Duck_t * thisDuck );
} Duck_Interface_Struct;
//
```

We'll also add this interface struct as the first member of our Duck struct.

```
// include/duck.r
typedef struct Duck_t
{
    Duck_Interface vtable;
    char name[MAX_CHARS_NAME];
} Duck_t;
```

When creating a new Duck object, now, we also need to make sure that this "vtable" points to the interface struct that defines the interface for our generic Ducks.

```
// source/duck.c
static Duck_Interface_Struct interface = {
    _duckShow
};

void
duckInit( Duck thisDuck, char * name )
{
    ...
    thisDuck->vtable = &interface;
    ...
}
```

The function `_duckShow()` is the function we'll use for Ducks or other derived objects that don't want to define their own function. It's prefixed with an underscore to prevent any sort of name-clashing with the publicly-available `duckShow()` function.

The definition for `duckQuack()` is straightforward, but the one for `duckShow()` looks a little odd. When this function runs, it is because some part of the code has called it on a Duck _or_ an object derived from Duck. We don't know at the outset which it is, but by following our conventions above, it doesn't matter: every Duck or object derived from Duck has a "vtable" which points to a Duck interface that contains a function pointer for the "show" function. Provided all of these pointers are defined, then all we need to do to call the correct function is reference that function pointer in the vtable.

```
// source/duck.c
void
duckShow( Duck thisDuck )
{
    if ( thisDuck && thisDuck->vtable && thisDuck->vtable->show )
    {
        thisDuck->vtable->show(thisDuck);
    }
}
```

Looking at a derived object may help this make more sense. Our "Mallard" objects "inherit" from Duck, so it includes a Duck_t object as it's first element.

```
// source/mallard.c
typedef struct Mallard_t
{
    Duck_t parentDuck;
    featherColor myColor;
} Mallard_t;
```

When we create a Mallard object, we now need to change the "vtable" to point to the list of functions that we want to be called for Mallard objects.

```
// source/mallard.c
static Duck_Interface_Struct interface = {
    mallardShow
};

void
mallardInit( Duck thisDuck, char * name, featherColor color )
{
    ...
    thisMallard->parentDuck.vtable = &interface;
    ...
}
```

Now, when `duckShow()` is called on a Mallard object, the function call `thisDuck->vtable->show(thisDuck)` points **not** to `_duckShow()` but to `mallardShow()`!

Of critical importance to this setup is that the Mallard functions do not operate on "Mallard" objects, but rather "Duck" objects.

```
// include/mallard.h
void mallardInit( Duck thisDuck, char * name, featherColor color );
```

Notice also that the function `mallardCreate()` does not return a Mallard object, but rather a Duck object.

```
// include/mallard.h
Duck mallardCreate( void );

// source/mallard.c
Duck
mallardCreate( void )
{
    ...
    return (Duck)newMallard;
}
```

This is what allows us to call Duck methods on Mallard objects without having to explicitly cast: although Mallard objects extend and behave differently than Duck objects, because they inherit from Duck, then can be treated by the rest of the program exactly as Ducks. The vtable then allows them to perform Mallard-specific implementations of the Duck functions. Thus, the Duck class is considered an "abstract data type" for which "Mallard" (and any other derived classes) offer an implementation.

One last thing to note is that this structure does not allow for full inheritance. Meaning, we couldn't use this same code to define a class that is derived from "Mallard" and then also expect to pass them to Duck functions without error. That problem will be solved in a future project.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
// source/main.c
int
main( void )
{    
    Duck George = duckCreate();
    Duck Bill = mallardCreate();
    
    printf("|__Initializing duck and mallard objects:\n");    -->    |__Initializing duck and mallard objects:

    duckInit(George, "George");                               -->        Initializing duck with name: George
    mallardInit(Bill, "Bill", BROWN);                         -->        Initializing new mallard duck with name: Bill
                                                                         Initializing duck with name: Bill

    printf("|__Quacking duck and mallard objects:\n");        -->    |__Quacking duck and mallard objects:
    
    duckQuack(George);                                        -->        George: Quack!
    duckQuack(Bill);                                          -->        Bill: Quack!
    
    printf("|__Showing duck and mallard objects:\n");         -->    |__Showing duck and mallard objects:
    
    duckShow(George);                                         -->        Hi! My name is George.
    duckShow(Bill);                                           -->        Hi! I'm a mallard duck. My name is Bill. I have brown feathers.
    
    return 0;
}
```

## References
- "Improving the Design with Dynamic Interface" from "TDD for Embedded C", pg 233
    - Code example: The ADT is a light controller for a home automation project. A number of different lights could be used in the home, so multiple implementations of the ADT are provided (one each for every type of light that could be used). The lights each have the same interface, so the application code can treat them all the same, while letting the specific implementations handle the details of turning themselves on or off.
        - Base class: [LightDriverPrivate.h](https://github.com/jwgrenning/tddec-code/blob/master/code-t3/include/devices/LightDriverPrivate.h) | [LightDriver.h](https://github.com/jwgrenning/tddec-code/blob/master/code-t3/include/devices/LightDriver.h) | [LightDriver.c](https://github.com/jwgrenning/tddec-code/blob/master/code-t3/src/devices/LightDriver.c)
        - Derived classes
            - [AcmeWirelessLightDriver.h](https://github.com/jwgrenning/tddec-code/blob/master/code-t3/include/devices/AcmeWirelessLightDriver.h) | [AcmeWirelessLightDriver.c](https://github.com/jwgrenning/tddec-code/blob/master/code-t3/src/devices/AcmeWirelessLightDriver.c)
            - [MemMappedLightDriver.h](https://github.com/jwgrenning/tddec-code/blob/master/code-t3/include/devices/MemMappedLightDriver.h) | [MemMappedLightDriver.c](https://github.com/jwgrenning/tddec-code/blob/master/code-t3/src/devices/MemMappedLightDriver.c)
            - [X10LightDriver.h](https://github.com/jwgrenning/tddec-code/blob/master/code-t3/include/devices/X10LightDriver.h) | [X10LightDriver.c](https://github.com/jwgrenning/tddec-code/blob/master/code-t3/src/devices/X10LightDriver.c)
- ["OOP in C", Section 3](https://www.state-machine.com/doc/AN_OOP_in_C.pdf), Miro Samek
    - [Code example](https://github.com/QuantumLeaps/OOP-in-C/tree/master/polymorphism)
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

To do this, we first need to define a table of function pointers for the abstract data type, "Duck", emphasis on the word "abstract". As opposed to our last project, we are going to prohibit the ability to create objects of the base class, which will make the implementation much easier (I'll return to creating objects of the base class in a later project). The table of function pointers will allow derived classes the ability to change the default function for a base class to one that's specific to the derived class. Our Duck object will have three functions which we will allow or require derived classes to change or implement (`show()`, `deinit()`, and `destroy()`) and one function which we will not (`duckQuack()`). Thus, the first three are included in our interface definition. In C++ parlance, this is a "vtable" or "table of virtual functions" (the "virtual" part means that they are intended to be defined by the derived classes). Each derived class will also need to write their own "Create" function(s). Making the "Create" functions polymorphic requires a bit more work and will be tackled in a [future project](https://github.com/nathancharlesjones/Comparison-of-OOP-techniques-in-C/tree/main/3c_Run-time-Polymorphism_ADT_Complete-interface).

```
// include/duck.r
typedef struct Duck_Interface_Struct const * Duck_Interface;
...
typedef struct Duck_Interface_Struct
{
    void (*show)( Duck_t * thisDuck );
    void (*deinit)( Duck_t * thisDuck );
    void (*destroy)( Duck_t * thisDuck );
} Duck_Interface_Struct;
//
```

The `show()` function will print something to the console. The `destroy()` function will free up the spot in memory where a Duck was being stored; it's always preceded by `deinit()` in order to allow for the clean-up of any parts of the derived class (such as ensuring a motor is returned home and powered off). Deinitialization operations are required to be in the `deinit()` function, as opposed to inside the `destroy()` function, since our base class has some data elements of it's own (`name`). The derived classes need to handle their own destroy operations (since they may be interacting with their own static memory pool) but the order of deinitializing should be derived object _first_, followed by base object (followed by returning the object to either the heap or static memory pool). If the base class were to have no explicit deinitialization, then the `deinit()` function in the interface struct could be omitted.

We'll also add the interface struct as the first member of our Duck struct.

```
// include/duck.r
typedef struct Duck_t
{
    Duck_Interface vtable;
    char name[MAX_CHARS_NAME];
} Duck_t;
```

The definition for `duckQuack()` is straightforward, but the ones for `duckShow()` and `duckDestroy()` look a little odd. When these functions run, it is because some part of the code has called them on an object derived from the Duck class. We don't know at the outset which derived class that might be, but by following our conventions above, it doesn't matter: every object derived from Duck has a "vtable" which points to a Duck interface that contains a function pointer for the "show" or "destroy" functions. Provided all of these pointers are defined, then all we need to do to call the correct function is reference that function pointer in the vtable. If one is not, as in the case of the Duck interface, then the "else" condition is executed (acting like a base or default implementation of `duckShow()` for objects that haven't provided their own implementation).

```
// source/duck.c
void
duckShow( Duck thisDuck )
{
    if ( thisDuck && thisDuck->vtable && thisDuck->vtable->show )
    {
        thisDuck->vtable->show(thisDuck);
    }
    else
    {
        printf("\tHi! My name is %s.\n", thisDuck->name);
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
static Duck_Interface_Struct interface_dynamic = {
    .show=mallardShow,
    .deinit=mallardDeinit,
    .destroy=mallardDestroy_dynamic
};

void
mallardInit( Mallard thisMallard, Duck_Interface interface, char * name, featherColor color )
{
    ...
    thisMallard->parentDuck.vtable = interface;
    ...
}
```

Now, when `duckShow()` is called on a Mallard object, the function call `thisDuck->vtable->show(thisDuck)` points to `mallardShow()`!

Of critical importance to this setup is that the Mallard functions do not operate on "Mallard" objects, but rather "Duck" objects.

```
// source/mallard.c
static void mallardShow( Duck thisDuck ){...}

// Matches function signature in Duck_Interface_Struct (include/duck.r):
// typedef struct Duck_Interface_Struct
// {
//     void (*show)( Duck_t * thisDuck );
//     ...
// } Duck_Interface_Struct;
```

Notice also that the functions `mallardCreate_XXX()` do not return a Mallard object, but rather a Duck object.

```
// include/mallard.h
Duck mallardCreate_dynamic( char * name, featherColor color );

// source/mallard.c
Duck
mallardCreate_dynamic( char * name, featherColor color )
{
    ...
    return (Duck)newMallard;
}
```

This is what allows us to call Duck methods on Mallard and Rubber duck objects without having to explicitly cast: although those objects extend and behave differently than Duck objects, because they inherit from Duck, then can be treated by the rest of the program exactly as Ducks. The vtable then allows them to perform Mallard- and Rubber-specific implementations of the Duck functions. Thus, the Duck class is considered an "abstract data type" for which "Mallard", "Rubber", and any other derived classes offer an implementation.

One last thing to note is that this structure does not allow for full inheritance. Meaning, we couldn't use this same code to define a class that is derived from "Mallard" and then also expect to pass them to Duck functions without error. That problem will be solved in a future project.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
// source/main.c
int
main( void )
{    
    printf("|__Creating duck and mallard objects\n");         -->    |__Creating duck and mallard objects

    Duck George = rubberCreate_dynamic("George", MEDIUM);
    Duck Bill = mallardCreate_static("Bill", BROWN);
    
    printf("|__Quacking duck and mallard objects:\n");        -->    |__Quacking duck and mallard objects:
    
    duckQuack(George);                                        -->        George: Quack!
    duckQuack(Bill);                                          -->        Bill: Quack!
    
    printf("|__Showing duck and mallard objects:\n");         -->    |__Showing duck and mallard objects:
    
    duckShow(George);                                         -->        Hi! I'm a medium rubber duck. My name is George.
    duckShow(Bill);                                           -->        Hi! I'm a mallard duck. My name is Bill. I have brown feathers.

    printf("|__Destroying duck and mallard objects:\n");      -->    |__Destroying duck and mallard objects

    duckDestroy(George);                                      -->        Deinitializing Rubber Duck object with name: George
                                                                         Deinitializing Duck object with name: George
    duckDestroy(Bill);                                        -->        Deinitializing Mallard object with name: Bill
                                                                         Deinitializing Duck object with name: Bill
    
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
# Run-time Polymorphism (ADT), Complete Interface

## Description

Our first attempt at run-time polymorphism (Projects [3a](https://github.com/nathancharlesjones/Comparison-of-OOP-techniques-in-C/tree/main/3a_Run-time-Polymorphism_ADT)/[3b](https://github.com/nathancharlesjones/Comparison-of-OOP-techniques-in-C/tree/main/3b_ADT-example-with-the-Template-Method-Pattern)) succeeded in allowing for a consistent interface once an object has been created. We could call `duckQuack()`, `duckShow()`, and `duckDestroy()` on any object that implemented the `Duck` base class, but _only after the object had already been created_ and we required a unique `Create()` function for each type of object we wanted to interact with in our code (`duckCreate_dynamic()`, `duckCreate_static()`, `mallardCreate_dynamic()`, and `mallardCreate_static()`). In some cases it might be useful to have a single `Create()` function which we can overload depending on the object we're trying to create (similar to the "vtable" in the base class that allows for derived classes to override the base class implementation of other functions). A function could then create an object which was defined on the command line or in an argument to the function and fully operate on that object without needing to know it's exact implementation. Accomplishing this involves a few modifications to our existing code.

First, consider that we want to take the four create functions listed above and condense them into a single overarching create function, like below. It will have to take some kind of input argument to inform it which object it needs to create.

```
Duck duckCreate( /* Something goes here to indicate which type of object to create */ );
```

Effectively we need some kind of function pointer to point to the specific "create" function we want. However, we already have a table of function pointers that each derived class defines for its objects: the "vtable". This list of function pointers uniquely defines each object and can easily be used to tell the `Create()` function which type of object to make. Provided we add a `create()` function to our vtable, the overarching function `duckCreate()` can just defer the actual object creation to the function that's defined in the vtable, just like for our other polymorphic functions.

```
// source/duck.c
const Duck_Interface_Struct duckDynamic = {
    .create=duckCreate_dynamic,
    .init=0,
    .show=0,
    .deinit=0,
    .destroy=duckDestroy_dynamic
};

Duck_Interface duckFromHeapMem = &duckDynamic;

const Duck_Interface_Struct duckStatic = {
    .create=duckCreate_static,
    .init=0,
    .show=0,
    .deinit=0,
    .destroy=duckDestroy_static
};

Duck_Interface duckFromStaticMem = &duckStatic;
```

We'll also need to add an `init()` function to the vtable since, similar to the process of destroying an object, the order of operations needs to be (1) object created by derived class, (2) initialization of base class variables, (3) initialization of derived class variables.

For the calling code to use these data values, we'll just need to "extern" them in the header files.

```
// include/duck.h
extern Duck_Interface duckFromHeapMem;
extern Duck_Interface duckFromStaticMem;
```

We'll start writing our single `Create()` function, making the first argument a pointer to `Duck_Interface_Struct` (aka `Duck_Interface`). Following that are any data values required to initialize the attributes of our `Duck` object (in this case, just `name`).

```
// include/duck.h
Duck duckCreate( Duck_Interface newDuckType, char * name, ... );
```

Following any required data values are three elipses (`...`), which is the C syntax for a variadic function. This tells the C compiler that this function may be called with any number of arguments after `name`, which is required for our project since we want to use this one function to create _all_ types of Ducks, even ones we haven't created yet. The "Mallard" class, for instance, requires a `featherColor` to be initialized, but we would have no idea ahead of time that this was a possibility. We have no idea how many and what types of data values all of our derived classes may need when they get created so we have to write our `Create()` function to accept an unknown number of them.

To use variadic arguments in C, we need to include the header "stdarg.h" and start and end our function with the following:

```
Duck
duckCreate( Duck_Interface newDuckType, char * name, ... )
{
    va_list args;
    va_start(args, name);
    ...
    va_end(args);
}
```

`va_list`, `va_start`, and `va_end` are macros that are defined in the "stdarg.h" header. `args` can be any valid C variable name and points to the list of variable arguments that gets past in through the elipses. The second argument to `va_start` (here, `name`) is the last required argument to the function.

We don't actually need any of these variable arguments in this function, but we do need to pass them to the derived object's `init()` function. To do that, we can pass a pointer to the list of arguments (`&args`) to that function.

```
// source/duck.c
newDuck->vtable->init(newDuck, &args); // Line 39
```

To accept this argument, the derived class's `init()` function needs to be defined to take an input of `va_list`.

```
// source/mallard.c
void mallardInit( Duck thisDuck, va_list * args ){...}
```

To pull out these arguments, we use the `va_arg()` macro, which takes in a `va_list` and a type of variable to access. The `va_list` effectively tells the C compiler where in the stack the list of variable arguments is stored and the variable type given to `va_arg()` tells it how much and what type of memory it's accessing.

```
// source/mallard.c
thisMallard->myColor = va_arg(*args, featherColor); // Line 58
```

And with that, our solution is complete. Our `main` function can now call a single create function, `duckCreate()`, with parameters that entirely define what type of object to create. It's interaction with this object is entirely through the interface, allowing it to operate exactly the same on different objects of different types (provided they all have a base class of `Duck`). To demonstrate the utility of this, I've rewritten our typical `main` function so that it accepts a few command line arguments that allow the user to define what type of object they want created.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
// source/main.c
int
main( void )
{    
    printf("|__Creating duck and mallard objects\n");         -->    |__Creating duck and mallard objects

    Duck George = duckCreate(duckFromStaticMem, "George");
    Duck Bill = duckCreate(mallardFromHeapMem, "Bill", WHITE);
    
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

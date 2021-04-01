- ADT can have virtual and unchanged functions; concrete class can add data and other methods (but can't be extending to further sublasses without modification)
- Data elements are all ADT type; User specifies which concrete class to use by which "...Create" method is called and needs to manually manage this (i.e. there is nothing the compiler can see that will tell it or the user later on in the code if a specific object is of one concrete type or another)

# Polymorphism (ADT)

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

We'll also add this interface struct as the first member of our Duck struct (we'll see why in a minute).

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
// include/mallard.r
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

Now, when `duckShow()` is called on a Mallard object, the function call `thisDuck->vtable->show(thisDuck)` points not to `_duckShow()` but to `mallardShow()`!

Of critical importance to this setup is that the Mallard functions do not operate on "Mallard" objects, but rather "Duck" objects. Notice also that the function `mallardCreate()` does not return a Mallard object, but rather a Duck object.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
|__Initializing duck and mallard objects:
        Initializing duck with name: George
        Initializing new mallard duck with name: Bill
        Initializing duck with name: Bill
|__Quacking duck and mallard objects:
        George: Quack!
        Bill: Quack!
|__Showing duck and mallard objects:
        Hi! My name is George.
        Hi! I'm a mallard duck. My name is Bill. I have brown feathers.
```

## References
- 
# OOP in ANSI C (Axel Schreiner)

## Description

Project 5a ended up being a fairly complete implementation of OOP in C (if I may say so myself) and taken purely from the perspective of functionality, it implements all or nearly all of the features that Axel Schreiner implements in his "OOP in ANSI C". However, his implementation ends up being much cleaner and more efficient than what I wrote in 5a (at the cost of some added complexity). If you're committed to using these OOP techniques on a large-ish project and want to use only the most thorough of implementations, this is the one for you.

Since we've built up nearly all of the same functionality, and since Axel does a fine job himself in his [book](https://www.cs.rit.edu/~ats/books/ooc.pdf), I'll refrain from describing how this code all works. Chapters 1-4, 6, and 8 of that book describe his OOP implemenation, in large part. The rest of the book is a mix of some complex examples that implement his OOP framework, an introduction to his preprocessor that automates the creating of the various .r/.h/.c files for new classes, and a few modifications to the basic OOP implementation that, in my opinion, aren't worth the effort.

I will, however, point out a few areas in which Axel's implementation is different to that which I stumbled upon in Project 5a.

1) The biggest difference, and perhaps the most important, is that Axel's implementation includes a base class called "Object", from which all other classes are derived and which is written in such a way that many of the functions can be reused by each derived class (compare the fact that he has only three type-checking functions ("isA", "isOf", and "isObject") while 5a has three _for each class_ ("objIsDuck"/"parentIsDuck"/"typeIsDuck", "objIsMallard"/"parentIsMallard"/"typeIsMallard", etc)). This results in derived classes being much more concise and easier to write: it took us 179 lines of code in Project 5a to add the `Mallard` class (not including the code to use static memory) but only 107 lines of code using Axel's implementation.

2) Axel gets around the problem of needing a "getParentInterface" function by declaring each class at runtime (`initMallard`, `initDuck`). This allows him to have a variable in each derived class which points to the base class in memory at the cost of some added complexity.

3) In addition to static memory, Axel's implementation lacks init/deinit functions and getter/setter functions (`duckSetName`, `mallardGetFeatherColor`). The init/deinit functions were only really necessary for us since each class had the ability to create objects from either heap or static memory. In that case, we had to separate the memory allocation/freeing from the initialization/deinitialization since derived classes would need to handle the former (in the case of a static memory pool) before allowing the base class to perform it's initialization (without allocating more space). If dynamic memory is being used, then the init/deinit functions could be combined with the ctor/store functions. In lieu of getter/setter functions, Axel creates macros in the private header files that give derived classes access to the data elements in the base classes (i.e. `#define	name(duck)	(((struct Duck *)(duck)) -> name)`). This is much simpler than what we have in 5a, but it also more tightly couples the derived classes to the base classes; if the format of the `name` or `myColor` variables changes, then some derived class code may need to change as well.

4) I observed some warnings about implicit casts on lines 132-138 of Object.c (inside `Class_ctor`). Oddly, I didn't see these same warnings inside either `DuckClass_ctor` or `MallardClass_ctor` and I did notice that in `Class_ctor` the code used `va_copy` but it didn't in the other functions.

5) For functions that can be dynamically overloaded (like `show`), Axel writes three separate functions: (1) `show`, which is called by the user's code and selects which implementation of `show` is actually called, (2) `Duck_show`, which provides a default implementation of `show` for the base class, and (3) `super_show`, which (to the best of my knowledge) would be used by a derived class which wanted to use the base class implementation of `show` instead of providing it's own. In contrast, Project 5a only has one function, `duckShow`, which calls an overloaded function if one is set and, otherwise, executes a default implementation. Derived classes can simply place a `NULL` or `0` value in the place of that function pointer if they don't want to override the base class implementation. I feel like this implementation is cleaner and simpler, but it's possible I'm not able to imagine a use case where my implementation doesn't work.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line. This program requires at least one command line argument to run.
- All arguments should be either "d" or "m" to denote the object type ("**d**uck" or "**m**allard").
- More than one "d" or "m" can be listed as long as each is separated by a space.

Running "make" simply runs the program with a default set of command line arguments ("d m"). You can run the executable in the "build" folder with other arguments, such as:
- ./build/5b_OOP-in-ANSI-C_Axel-Schreiner.out m d d
- ./build/5b_OOP-in-ANSI-C_Axel-Schreiner.out d
- ./build/5b_OOP-in-ANSI-C_Axel-Schreiner.out m m m
- etc.

## Expected output

```
// For default command-line arguments: "m d"
Freida: I'm migrating!
Hi! I'm a mallard duck. My name is Freida. I have brown feathers.
Freida: Quack!
Initializing duck with name: Freida
Hi! My name is Freida.
Freida: Quack!
```

## References
- "OOP in ANSI C" by Axel Schreiner (primarily chapters 1-4, 6, and 8).
    - [PDF](https://www.cs.rit.edu/~ats/books/ooc.pdf)
    - [Git repo](https://github.com/shichao-an/ooc)

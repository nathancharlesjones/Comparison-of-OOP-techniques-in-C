# OOP in ANSI C (Axel Schreiner)

## Description

Project 5a ended up being a fairly complete implementation of OOP in C (if I may say so myself) and taken purely from the perspective of functionality, it implements all or nearly all of the features that Axel Schreiner implements in his "OOP in ANSI C". However, his implementation ends up being much cleaner and more efficient than what I wrote in 5a (at the cost of some added complexity). If you're committed to using these OOP techniques on a large-ish project and want to use only the most thorough of implementations, this is the one for you.

Since we've built up nearly all of the same functionality, and since Axel does a fine job himself in his [book](https://www.cs.rit.edu/~ats/books/ooc.pdf), I'll refrain from describing how this code all works. Chapters 1-4, 6, and 8 of that book describe his OOP implemenation, in large part. The rest of the book is a mix of some confusing examples that implement his OOP framework, an introduction to his preprocessor that automates the creating of the various .r/.h/.c files for new classes, and a few modifications to the basic OOP implementation that, in my opinion, aren't worth the effort.

I will, however, point out a few areas in which Axel's implementation is superior to that which I stumbled upon in Project 5a.

- Compare SLOC
    - 5a
        - Total (minus redMallard): 455; 372 w/o static memory option
        - duck (.r/.h/.c): 234 (26 + 14 + 194); 193 w/o static memory option
        - mallard (.r/.h/.c): 221 (18 + 13 + 190); 179 w/o static memory option
    - 5b
        - Total: 479
        - Object (.r/.h/.c): 260 (24 + 22 + 214)
        - duck (.r/.h/.c): 112 (18 + 9 + 85)
        - mallard (.r/.h/.c): 107 (17 + 9 + 81)
- No init/deinit, static memory, getters/setters
- Runtime declaration of classes
- Warnings about implicit casts
- Separate default and selector functions
- Seems to expect derived classes to be aware of certain functions, i.e. super_draw, casts
- Parameterizes isObj, isType

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
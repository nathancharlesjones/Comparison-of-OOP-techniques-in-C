# Using generic macros for polymorphism

- Attempt to use generic macros to implement polymorphism
- Sort of works; macros are evaluated at compile-time so the object type has to be known ahead of time. So it's more like "compile-time polymorphism" than "run-time polymorphism". Also it weirdly puts the interface into two files and requires name mangling ("duckShow" vs "_duckShow"). But I did manage to get rid of the private headers! 
    - Removing the private headers was a happy by-product of needing to define "inherited" functions for all subclasses. Since the generic macro won't re-cast the input argument, in order for something like "duckShow(X)" to work on multiple data types without objection from the compiler, there needs to be a "show"-like function for each different object to which the generic macro can dispatch. Since each object has to reimplement all of the parent class's functions anyways, there didn't seem to be any sense in using the private headers to embed each parent object into the struct of the child object.
- It also requires all parent class interfaces to "know" about subclass implementations (notice how "duckInterface.h" needs to include both "mallard.h" and "redMallard.h" in order to understand the functions that the generic macros are trying to call for Mallard and redMallard objects).
- No way to assert when the default option is taken, but maybe that's a non-issue since the compiler will prevent the program from even compiling if there isn't a data type that matches the generic list.

# References
- ["C11 - Generic Selections"](http://www.robertgamble.net/2012/01/c11-generic-selections.html) (Rob's Programming Blog)
# Run-time Polymorphism (Inheritable)

## Description

While the second project introduced the concept of simple inheritance (the idea that if I embed a base class object as the first element to a derived class object, then a pointer to the derived class _is also_ a pointer to the base class portion of that object), it also introduced two problems with that simplified approach: (1) each class still only operated on it's own data type, requiring explicit casts to other data types when calling base class methods (e.g. `duckShow((Duck)myMallard))`), and (2) the base class methods had no concept of any of the derived classes so they couldn't really behave polymorphically (e.g. `duckShow((Duck)myMallard))` only showed the `Duck` message, not the `Mallard` message). Projects 3a/3b/3c solved these two problems, but only by restricting the base class to an "abstract data type", whose implementation was fulfilled by one of many derived classes, with the layers of derived classes only going one level deep. In this project, we're going to backtrack a bit on our solution in order to create a framework that's truly inheritable. The final result will still behave polymorphically, but it go back to requiring explicit casts.



## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```

```

## References

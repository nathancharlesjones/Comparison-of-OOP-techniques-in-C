# Comparison of OOP techniques in C

A collection of ways to use OOP techniques in C, organized from least to most complicated. Each project demonstrates and briefly describes a different technique which (mostly) build upon one another.

The complexity starts to skyrocket after Project 3c, so that's probably the last one I would consider using in any of my projects (if I have to debug something, I want it to be the thing I'm trying to build, not the framework I'm relying on to work). The later projects get more complete and more thorough (with Axel Schreiner's implementation being practically a version of C++ written completely in C), but given their complexity I feel like they're solidly in the camp of "For the love of God, just use use C++ already". This limits any of my OOP-style programming to just abstract data types (as opposed to a full inheritance structure), but so far I haven't found a strong need for the latter. In fact, we only need the projects leading up to and including 3c to demonstrate three different design patterns (Mediator, Template Method, and Factory) and, if I'm not mistaken, none of the techniques in "Design Patterns for Embedded Systems in C" require anything more complicated than the very first project (1a).

Mermaid test

```mermaid
  graph TD;
      A-->B;
      A-->C;
      B-->D;
      C-->D;
```

## References

- "OOP in C" by Miro Samek
    - [PDF](https://www.state-machine.com/doc/AN_OOP_in_C.pdf)
    - [Git repo](https://github.com/QuantumLeaps/OOP-in-C)
- "Test-driven Development for Embedded C" by James Grenning
    - [Book](https://www.amazon.com/Driven-Development-Embedded-Pragmatic-Programmers/dp/193435662X/ref=sr_1_2?dchild=1&keywords=tdd+for+embedded+c&qid=1616668590&sr=8-2)
    - [Git repo](https://github.com/jwgrenning/tddec-code)
- "OOP in ANSI C" by Axel Schreiner.
    - [PDF](https://www.cs.rit.edu/~ats/books/ooc.pdf)
    - [Git repo](https://github.com/shichao-an/ooc)
- ["Design Patterns for Embedded Systems in C"](https://www.amazon.com/Design-Patterns-Embedded-Systems-Engineering/dp/1856177076) by Bruce Powel Douglass

# ADT Example with the Template Method Pattern

## Description

Although our current implementation of OOP in C pales in comparison to a true OOP language like C++, I've found that it's sufficient for most C projects that require OOP-style programming. In fact, I discovered that using this accumulation of techniques alone, I was able to program each of the design patterns discussed in the book ["Head First Design Patterns"](https://www.amazon.com/Head-First-Design-Patterns-Brain-Friendly/dp/0596007124), which uses Java for all of it's examples (which is an OOP language). You can learn more about design patterns and try your hand at implementing your own using these techiques by reading that book, ["Design Patterns for Embedded Systems in C"](https://www.amazon.com/Design-Patterns-Embedded-Systems-Engineering/dp/1856177076), the [original book on design patterns](https://www.amazon.com/Design-Patterns-Object-Oriented-Addison-Wesley-Professional-ebook/dp/B000SEIBB8), or online articles like [this one](https://www.geeksforgeeks.org/software-design-patterns/) from GeeksforGeeks.

In the "Template Method" pattern, we have an algorithm with multiple steps which are each implemented in potentially different ways. Although we could simply let each derived class implement the entire algorithm on their own, this results in unnecessarily repeated code and, more importantly, exposes the actual algorithm to each derived class. If the algorithm were ever to change, we would need to individually change each derived class as a result. This pattern allows a single ADT to control the execution of the algorithm.

In this example, we're creating an ADT called `CaffeinatedBeverage` with a `prepare()` method and two derived classes, `Tea` and `Coffee`. Thus, we'll be able to create `Tea` and `Coffee` objects and "prepare" them. The preparation algorithm is pretty similar for each drink: we need to boil some water, brew our drink (either steeping the tea or pouring the hot water over some coffee grinds), pour our drink into a cup, add some condiments (either lemon for the tea or milk and sugar for the coffee), and lastly, possibly add whipped cream (for the coffee). Thus, our "prepare" algorithm has these five steps:
1. Boil water
2. Brew
3. Pour into cup
4. Add condiments
5. Add whipped cream

We don't want each of the derived classes to re-implement this entire method, just the individual pieces as needed, so we'll use the "Template Method" pattern. To accomplish this, notice how our `prepare()` method merely calls functions associated with the five steps above:

```
// source/CaffeinatedBeverage.c
void CaffeinatedBeverage_prepare(CaffeinatedBeverage _self) {
    printf("|__Making beverage with name: %s\n", _self->name);
    CaffeinatedBeverage_boilWater(_self);
    CaffeinatedBeverage_brew(_self);
    CaffeinatedBeverage_pourInCup(_self);
    CaffeinatedBeverage_addCondiments(_self);
    CaffeinatedBeverage_addWhip(_self);
}
```

These functions are all implemented in `CaffeinatedBeverage.c`. The `boilWater()` and `pourInCup()` functions are the same for each derived class, so these are implemented in this same source file (and are pointedly absent from our interface struct, which prevents any derived class from overriding their implementations).

```
// include/CaffeinatedBeverage.r
typedef struct CaffeinatedBeverage_Interface_Struct {
    void (*brew)(CaffeinatedBeverage_Data_Struct*);
    void (*addCondiments)(CaffeinatedBeverage_Data_Struct*);
    void (*addWhip)(CaffeinatedBeverage_Data_Struct*);
    ...
} CaffeinatedBeverage_Interface_Struct;
```

The `brew()`, `addCondiments()`, and `addWhip()` functions all forward on to implementations in the derived classes. In this manner, the derived classes only need to concern themselves with these three implementations, not the implementation of the "prepare" algorithm itself. If the algorithm were to change (say we needed to add a general clean-up step at the end), we would only need to make this change in one place.

## How do I run it?

Download or clone this repository. Navigate to this folder and then run "make" or "make clean && make" from the command line.

## Expected output

```
// source/main.c
int
main(void)
{
    printf("|__Creating beverage objects\n");                          -->  |__Creating beverage objects

    CaffeinatedBeverage Tea1 = newTea_dynamic("Josephine's tea");      -->      Initializing new tea drink with name: Josephine's tea
    CaffeinatedBeverage Coffee1 = newCoffee_static("Deidra's coffee"); -->      Initializing new coffee drink with name: Deidra's coffee

    printf("|__Preparing beverage objects\n");                         -->  |__Preparing beverage objects
    
    CaffeinatedBeverage_prepare(Tea1);                                 -->  |__Making beverage with name: Josephine's tea
                                                                                Boiling water.
                                                                                Steeping the tea.
                                                                                Pouring into cup.
                                                                                Adding lemon.
    CaffeinatedBeverage_prepare(Coffee1);                              -->  |__Making beverage with name: Deidra's coffee
                                                                                Boiling water.
                                                                                Dripping coffee through filter.
                                                                                Pouring into cup.
                                                                                Adding sugar and milk.
                                                                                Adding whip.

    printf("|__Destroying beverage objects\n");                        -->  |__Destroying beverage objects

    CaffeinatedBeverage_destroy(Tea1);                                 -->      Deinitializing caffeinated beverage object with name: Josephine's tea
    CaffeinatedBeverage_destroy(Coffee1);                              -->      Deinitializing caffeinated beverage object with name: Deidra's coffee

    return 0;
}
```

## References
- ["Head First Design Patterns"](https://www.amazon.com/Head-First-Design-Patterns-Brain-Friendly/dp/0596007124), Chapter 8
- ["Template Method Design Pattern"](https://www.geeksforgeeks.org/template-method-design-pattern/), GeeksforGeeks

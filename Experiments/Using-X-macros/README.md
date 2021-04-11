# Using X-macros

- In some of the projects, there are objects that define enumerated qualities (featherColor, size) in the header file and then list a string name in the source file which is to be associated with the enumerated type. I.e.

```
// Header
typedef enum {RED, BROWN, WHITE} featherColor;

// Source
const char * colorNames[] = {"red", "brown", "white"};
```

- Although this is a short list with only one associated piece of data (the string name), the lists could easily get out-of-sync with each other after enough edits, especially since they exist in different files. One solution (albeit not a great one), is to use a technique called "X macros". This technique places the enum value and the string value in the same place, then uses the C preprocessor to generate the enum type and the list of string names. I'll not show the code here (it's kind of gross) and I'll refrain from further explanation since the reference below does as good as job as I would ever do. Good to know this technique exists and works, though.

## References
- ["Abusing the Preprocessor, Almost"](http://technobar.blogspot.com/2013/12/abusing-preprocessor-almost.html?m=1)
# Using "typedef" for type overloading

- Attempt to use "typedef" to get C to treat derived class data types as equivalent to the base class data type
- Couldn't get this to work. The "typedef" keyword works similar to #define, so the derived class was just treated exactly like the base class (meaning that methods defined for the derived class stopped working unless the object was cast to the type of the derived class).
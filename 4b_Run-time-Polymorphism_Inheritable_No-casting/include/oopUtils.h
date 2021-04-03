#ifndef OOP_UTILS_H
#define OOP_UTILS_H

#include "baseClass.r"

#define GET_TYPE_FROM_OBJ(X) (*(BaseClass_Interface *)X)
#define GET_PARENT_FROM_TYPE(X) (*(BaseClass_Interface *)X)

#endif // OOP_UTILS_H
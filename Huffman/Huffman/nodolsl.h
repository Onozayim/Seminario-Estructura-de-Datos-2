#ifndef NODOLSL_H
#define NODOLSL_H
#include <iostream>

struct NodoLSL
{
    T dato;
    NodoLSL* siguiente;
    NodoLSL(const T& elem, NodoLSL* sig = nullptr):
        dato(elem),
        siguiente(sig)
    {}
};

#endif // NODOLSL_H

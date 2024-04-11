#ifndef NODEL_H_INCLUDED
#define NODEL_H_INCLUDED

class NodoL
{
public:

    NodoL();
    void setNext(NodoL*);
    void setPrev(NodoL*);
    void setLeft(NodoL*);
    void setRight(NodoL*);
    void setFrecuencia(int);
    void setCaracter(char);
    void aumentarFrecuencia();

    NodoL* getNext();
    NodoL* getPrev();
    NodoL* getLeft();
    NodoL* getRight();
    int getFrecuencia();
    char getCaracter();

private:
    int frecuencia;
    char caracter;

    NodoL* next;
    NodoL* prev;
    NodoL* left;
    NodoL* right;

};


#endif // NODEL_H_INCLUDED

#ifndef RESTAURANTE_H
#define RESTAURANTE_H

#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

#include "platillo.h"
#include "list.h"

using namespace std;

class Menu
{
public:
    Menu();

    void crearP(Platillo &p);
    void mostrar(Platillo &p);
    void escribir(const Platillo &p);
    void MostrarP();
    void coding();

    void BuscarP();
    void ModificarP();
    void Eliminar_F_P();
    void Eliminar_L_P();
    void ActivarP();

    void Huffman();
    void cargarFrase();
    void mostrarLista();
    void listaOrdenada();
    void mostrarListaArbol();

    void mostrarDiccionario();

    void descifrado();


    int getCont() const;
    void setCont(int value);

    string getTexto() const;
    void setTexto(const string &value);

private:
    int cont=0;
    List lista;
    string texto;

};

#endif // RESTAURANTE_H

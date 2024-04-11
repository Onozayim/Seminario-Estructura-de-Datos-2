#ifndef GRUPO_H
#define GRUPO_H


#include "Grupo.h"


class Grupo
{
    public:
        Grupo();
        virtual ~Grupo();

        char idGrupo[3];
        char grado[3];
        char grupo[3];
        char encargado[50];
        char numAlumnos[3];
        char salon[10];

        void agregar();
        void imprimir();
        void buscar();
        void modificar();
        void eliminar();

        void generarIndice();
        void mostrarIndice();

    protected:

    private:
};

#endif // GRUPO_H

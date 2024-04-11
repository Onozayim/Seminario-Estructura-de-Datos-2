#ifndef PAGOS_H
#define PAGOS_H

#include "ConceptoPago.h"

class Pagos
{
    public:
        Pagos();
        virtual ~Pagos();

        int idAlumno = 0;
        int idPago = 0;

        ConceptoPago pagos[7200];

        void agregar();
        void mostrar();
        void buscar();
        void eliminar();
        void modificar();

    protected:

    private:
};

#endif // PAGOS_H

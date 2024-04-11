#ifndef CONCEPTOPAGO_H
#define CONCEPTOPAGO_H


class ConceptoPago
{
    public:
        ConceptoPago();
        virtual ~ConceptoPago();

        char idAlumno[4];
        char idPago[4];
        char nombreALumno[50];
        char nombreTutor[50];
        char nombreTutora[50];
        char cantidadPago[6];
        char fecha[11];


    protected:

    private:
};

#endif // CONCEPTOPAGO_H

#ifndef TRABAJADOR_H
#define TRABAJADOR_H


class Trabajador
{
    public:
        Trabajador();
        virtual ~Trabajador();

        void agregar();
        void imprimir();
        void imprimirTrabajador(Trabajador tra);
        void buscar();
        void modificar();
        void eliminar();

        void generarGrafos();
        void mostrarGrafos();

        char id[3];
        char nombre[25];
        char apellidoP[25];
        char apellidoM[25];
        char salario[6];
        char area[20];
        char horario[20];

    protected:

    private:
};

#endif // TRABAJADOR_H

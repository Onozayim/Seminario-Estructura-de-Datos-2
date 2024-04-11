#include <iostream>
#include "Trabajador.h"

using namespace std;

using namespace std;

int main()
{
    int op;

    do
    {
        Trabajador cs;
        cout << "1)Agregar" << endl
             << "2)Imprimir" << endl
             << "3)Buscar" << endl
             << "4)Meodificar" << endl
             << "5)Eliminar" << endl
             << "6)Generar Grafos" << endl
             << "7)Mostrar Grafos" << endl
             << "8)Salir" << endl << endl;

        cin >> op;

        switch (op)
        {
        case 1:
            cs.agregar();
            break;
        case 2:
            cs.imprimir();
            break;
        case 3:
            cs.buscar();
            break;
        case 4:
            cs.modificar();
            break;
        case 5:
            cs.eliminar();
            break;
        case 6:
            cs.generarGrafos();
            break;
        case 7:
            cs.mostrarGrafos();
            break;
        default:
            break;
        }

        system("pause");
        system("cls");

    }
    while(op != 8);
    return 0;
}

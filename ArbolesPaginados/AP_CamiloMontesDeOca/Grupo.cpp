#include "Grupo.h"
#include "ArbolB.h"

#include "iostream"
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include <list>

using namespace std;

int pagina = 0;

struct Pagina {
    int numPagina;
    int numLlaves;
    int arregloLLaves[3] = {0,0,0};
    vector<int> apuntador;
};

struct Pares {
    int num;
    char letra;
};

list<Pagina> listaPag;
list<Pares> listaPares;

template<class T,int order>
class ArbolB;

template<class T,int order>
class NodoArbolB {
    private:
        T *llavesNAB;
        NodoArbolB **hijosNAB;
        NodoArbolB *padresNAB;
        int numLlaveNAB;
        bool hoja;
        int numPaginaNAB;
        int pagina = 0;

    public:
        friend class ArbolB<T,order>;

        NodoArbolB() {
            padresNAB = NULL;
            numLlaveNAB = 0;
            hoja = true;
            llavesNAB = new T[order];
            hijosNAB = new NodoArbolB * [order + 1];

            for(int i = 0; i < order; i++)
                hijosNAB[i] = NULL;

            hijosNAB[order] = NULL;
            numPaginaNAB = pagina++;
        }

        ~NodoArbolB() {
            delete[]llavesNAB;
            delete[]hijosNAB;
        }

        void divNodos(NodoArbolB *&raiz) {
            if(this->numLlaveNAB <= order - 1)
                return;

            int ind = this->numLlaveNAB / 2;
            int i = ind + 1, j = 0;

            NodoArbolB *nvoNodo = new NodoArbolB();

            while(i < this->numLlaveNAB) {
                nvoNodo->llavesNAB[j] = this->llavesNAB[i];
                nvoNodo->numLlaveNAB++;
                i++;
                j++;
            }

            i = ind + 1, j = 0;

            while(i < numLlaveNAB + 1) {
                nvoNodo->hijosNAB[j] = hijosNAB[i];

                if(hijosNAB[i] != NULL)
                    nvoNodo->hijosNAB[j]->padresNAB=nvoNodo;

                if(hijosNAB[i] != NULL)
                    nvoNodo->hoja = false;

                i++;
                j++;
            }

            this->numLlaveNAB=ind;

            if(this->padresNAB == NULL) {
                padresNAB = new NodoArbolB();
                padresNAB->hijosNAB[0] = this;
                raiz = padresNAB;
                raiz->hoja = false;
            }

            for(i = padresNAB->numLlaveNAB; i>= 0; i--) {
                if(i == 0 || padresNAB->llavesNAB[i - 1] <= llavesNAB[ind]) {
                    padresNAB->llavesNAB[i] = llavesNAB[ind];
                    padresNAB->hijosNAB[i + 1] = nvoNodo;
                    break;
                }
                else if(padresNAB->llavesNAB[i - 1] > llavesNAB[ind]) {
                    padresNAB->llavesNAB[i] = padresNAB->llavesNAB[i - 1];
                    padresNAB->hijosNAB[i + 1] = padresNAB->hijosNAB[i];
                }
            }

            padresNAB->llavesNAB++;
            nvoNodo->padresNAB = padresNAB;
            padresNAB->divNodos(raiz);
        }

        void recorrerArbol(int nivel) {
            struct Pagina temporal;

            for(int i = 0; i < numLlaveNAB; i++) {
                temporal.arregloLLaves[i] = llavesNAB[i];
                temporal.numLlaves = numLlaveNAB;
                temporal.numPagina = numPaginaNAB - 1;
            }

            for(int i = 0; i <= numLlaveNAB; i++) {
                if(!hoja) {
                    int valor = hijosNAB[i]->numPaginaNAB - 1;
                    temporal.apuntador.push_back(valor);
                }
            }

            listaPag.push_back(temporal);

            if(this->hoja)
                return;

            for(int i=0; i<numLlaveNAB+1; i++)
                hijosNAB[i]->recorrerArbol(nivel+2);
        }
};

template<class T,int order>
class ArbolB {
    private:
        NodoArbolB<T,order> *raiz;
    public:
        ArbolB() {
            raiz=NULL;
        }

        ~ArbolB() {
            delete raiz;
        }

        void insertAB(int llve) {
            NodoArbolB<T,order> *currNodo=raiz;

            if(raiz == NULL) {
                raiz = new NodoArbolB<T,order>();
                raiz->llavesNAB[raiz->numLlaveNAB] = llve;
                raiz->numLlaveNAB++;
                raiz->numPaginaNAB=pagina++;
            }

            else {
                int nodoaRecorrer = 0;

                while(!currNodo->hoja) {
                    nodoaRecorrer = currNodo->numLlaveNAB;

                    for(int i = 0; i < currNodo->numLlaveNAB; i++) {
                        if(currNodo->llavesNAB[i] > llve) {
                            nodoaRecorrer = i;
                            break;
                        }
                    }
                    currNodo = currNodo->hijosNAB[nodoaRecorrer];
                }

                for(int i = currNodo->numLlaveNAB; i >= 1; i--) {
                    if(currNodo->llavesNAB[i - 1] > llve) {
                        currNodo->llavesNAB[i] = currNodo->llavesNAB[i - 1];
                        currNodo->llavesNAB[i - 1] = llve;
                    }
                    else {
                        currNodo->llavesNAB[i]=llve;
                        break;
                    }
                }

                currNodo->numLlaveNAB++;
                currNodo->divNodos(raiz);
            }
        }

        void imprimirAB() {
            if(raiz == NULL)
                return;

            raiz->recorrerArbol(0);
        }
};

Grupo::Grupo()
{
    //ctor
}

Grupo::~Grupo()
{
    //dtor
}

bool comparar(const Pagina &primero, const Pagina &segundo) {
    return primero.numPagina < segundo.numPagina;
}

void imprimirLetraTxt(list<Pares> g, int llave, fstream &fout) {
    list<Pares>::iterator iter;

    for(iter = g.begin(); iter != g.end(); iter++) {
        if(iter->num == llave)
            fout << iter->letra;
    }
}

void imprimirLetra(list<Pares> g,int llave) {
    list<Pares>::iterator iter;

    for(iter = g.begin(); iter != g.end(); ++iter) {
        if(iter->num == llave)
            cout << iter->letra;
    }
}

void generarTXT(list<Pagina> g) {
    fstream arbol("Arbol.txt",ios::out);
    list<Pagina>::iterator iter;

    arbol << "\tNo.Pagina\tContador de Llaves\tArreglo de Llaves\tArreglo de hijos\t\t\t\t\n";

    for(iter = g.begin(); iter != g.end(); ++iter) {
        arbol << "\t" << iter->numPagina << "\t";
        arbol << "\t" << iter->numLlaves << "\t\t";
        arbol << "\t\t";

        for(int i = 0; i < 3; i++) {
            if(iter->arregloLLaves[i] != 0)
                arbol << "[";

            if(iter->arregloLLaves[i] == 0)
                arbol << " ";

            if(iter->arregloLLaves[i] != 0) {
                arbol << iter->arregloLLaves[i];
                imprimirLetraTxt(listaPares,iter->arregloLLaves[i],arbol);
            }
            if(iter->arregloLLaves[i] != 0)
                arbol << "]";
        }

        unsigned int vecSize = iter->apuntador.size();
        arbol << "\t\t\t";

        if(vecSize == 0) {
            for(int i = 0; i < iter->numLlaves+1; i++)
                arbol << "";

            if(iter->numLlaves == 1)
                arbol << "\t";

            arbol << " \t\t";
        }

        for(unsigned int i = 0; i < vecSize; i++) {
            arbol << " " << iter->apuntador[i] << "   ";

            if(vecSize == 2)
                arbol << "\t";

            if(vecSize == 3)
                arbol << " ";

            if(i == vecSize - 1)
                arbol << "\t";
        }

        if(iter->numLlaves == 2)
            arbol << "\t\t\t";

        arbol << '\n';
    }
}

void imprimList(list<Pagina> g) {
    list<Pagina>::iterator iter;

    cout  << "\tNo.Pagina\tContador de Llaves\tArreglo de Llaves\tArreglo de hijos\t\t\t\t\n";

    for(iter = g.begin(); iter != g.end(); ++iter) {
        cout << "\t" << iter->numPagina << "\t";
        cout << "\t" << iter->numLlaves << "\t";
        cout << "\t\t";

        for(int i = 0; i < 3; i++) {
            if(iter->arregloLLaves[i] != 0)
                cout << "[";

            if(iter->arregloLLaves[i] == 0)
                cout << " ";

            if(iter->arregloLLaves[i] != 0) {
                cout << iter->arregloLLaves[i];
                imprimirLetra(listaPares, iter->arregloLLaves[i]);

                if(iter->arregloLLaves[i] < 10)
                    cout << " ";
            }
            if(iter->arregloLLaves[i] != 0)
                cout << "]";
        }

        unsigned int vecSize = iter->apuntador.size();

        if(vecSize == 0) {
            for(int i=0; i < iter->numLlaves+1; i++)
                cout << "";

            if(iter->numLlaves == 1)
                cout << "\t";

            cout << " \t\t";
        }

        for(unsigned int i = 0; i < vecSize; i++) {
            cout << " " << iter->apuntador[i] << "   ";

            if(vecSize == 2)
                cout << "\t";

            if(vecSize == 3)
                cout << " ";

            if(i == vecSize - 1)
                cout << "\t";
        }
        if(iter->numLlaves == 2)
            cout << "\t\t\t";

        cout << '\n';
    }
}

void obtenerInfo() {
    ifstream archivo("Grupos.bin", ios::in);

    if(!archivo.good())
    {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    Grupo con;

    while(!archivo.eof())
    {
        archivo.read((char*)&con, sizeof(con));

        if(!archivo.eof())
        {
            cout << "Id grupo: " << con.idGrupo << endl;
            cout << "Grado del grupo: " << con.grado << endl;
            cout << "Grupo (A,B,C): " << con.grupo << endl;
            cout << "Nombre encargado: " << con.encargado << endl;
            cout << "Numero de alumnos: " << con.numAlumnos << endl;
            cout << "Salon: " << con.salon << endl <<endl;

            int x = con.idGrupo[0] - '0';
            int y = con.grado[0] - '0';
            int z = con.grupo[0] - '0';

            string cad = to_string(x);
            string cad2 = to_string(y);
            string cad3 = cad + cad2;

            int numero = stoi(cad3);

            Pares temporal;
            temporal.num = numero;
            temporal.letra = z;
            listaPares.push_back(temporal);
        }
    }
}

void LlenarArbol(list<Pares> g) {
    ArbolB<int,4> t1;
    pagina = 0;
    list<Pares>::iterator iter;

    for(iter = g.begin(); iter != g.end(); ++iter)
        t1.insertAB(iter->num);

    t1.imprimirAB();
}


void Grupo::agregar()
{
    Grupo con;

    cout << "Ingrese id del grupo: ";
    fflush(stdin);
    cin.getline(con.idGrupo, 3);

    cout << "Ingrese el grado: ";
    fflush(stdin);
    cin.getline(con.grado, 3);

    cout << "Ingrese el grupo: ";
    fflush(stdin);
    cin.getline(con.grupo, 3);

    cout << "Ingrese el nombre del encargado: ";
    fflush(stdin);
    cin.getline(con.encargado, 50);

    cout << "Ingrese el numero de alumnos: ";
    fflush(stdin);
    cin.getline(con.numAlumnos, 3);

    cout << "Ingrese el salon del grupo: ";
    fflush(stdin);
    cin.getline(con.salon, 10);

    ofstream archivo("Grupos.bin", ios::app);
    archivo.write((char*)&con, sizeof(con));
    archivo.close();

    //con el ios::app, se abre al archivo al final, y no sobreescribe
    // con el ios::binary se abre al inicio, y se sobreescribe
    //no hay problema?
}

void Grupo::imprimir()
{

    ifstream archivo("Grupos.bin", ios::in);

    if(!archivo.good())
    {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    Grupo con;

    while(!archivo.eof())
    {
        archivo.read((char*)&con, sizeof(con));

        if(!archivo.eof())
        {
            cout << "Id grupo: " << con.idGrupo << endl;
            cout << "Grado del grupo: " << con.grado << endl;
            cout << "Grupo (A,B,C): " << con.grupo << endl;
            cout << "Nombre encargado: " << con.encargado << endl;
            cout << "Numero de alumnos: " << con.numAlumnos << endl;
            cout << "Salon: " << con.salon << endl <<endl;
        }
    }
}

void Grupo::buscar()
{

    ifstream archivo("Grupos.bin", ios::in);
    char idPago[4];

    if(!archivo.good())
    {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    cout << "Ingrese el id del grupo a buscar: " << endl;
    fflush(stdin);
    cin.getline(idPago, 4);

    Grupo con;

    while(!archivo.eof())
    {
        archivo.read((char*)&con, sizeof(con));

        if(!archivo.eof() && strcmp(con.idGrupo, idPago) == 0)
        {
            cout << "Id grupo: " << con.idGrupo << endl;
            cout << "Grado del grupo: " << con.grado << endl;
            cout << "Grupo (A,B,C): " << con.grupo << endl;
            cout << "Nombre encargado: " << con.encargado << endl;
            cout << "Numero de alumnos: " << con.numAlumnos << endl;
            cout << "Salon: " << con.salon << endl <<endl;

            archivo.close();
            return;
        }
    }

    archivo.close();
    cout << "Grupo no encontrado" << endl;
}

void Grupo::modificar()
{

    ifstream archivo("Grupos.bin", ios::in);
    char idPago[4];
    int op, op2;

    if(!archivo.good())
    {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    cout << "Ingrese el id del grupo a modificar: " << endl;
    fflush(stdin);
    cin.getline(idPago, 4);

    Grupo con;

    while(!archivo.eof())
    {
        archivo.read((char*)&con, sizeof(con));

        if(!archivo.eof() && strcmp(con.idGrupo, idPago) == 0)
        {
            cout << "Id grupo: " << con.idGrupo << endl;
            cout << "Id grupo: " << con.idGrupo << endl;
            cout << "Grado del grupo: " << con.grado << endl;
            cout << "Grupo (A,B,C): " << con.grupo << endl;
            cout << "Nombre encargado: " << con.encargado << endl;
            cout << "Numero de alumnos: " << con.numAlumnos << endl;
            cout << "Salon: " << con.salon << endl <<endl;

            cout << "Estas seguro que quieres modificar este grupo (si == 1)? ";
            cin >> op;

            archivo.close();
        }
    }

    if(op == 1)
    {
        cout << "SI" << endl;
        ifstream mod("Grupos.bin", ios::in);
        ofstream temp("Temp.bin", ios::binary);

        if(!mod.good())
        {
            cout << "Archivo no encontrado" << endl;
            return;
        }

        while(!mod.eof())
        {
            mod.read((char*)&con, sizeof(con));
            if(!mod.eof() && strcmp(con.idGrupo, idPago) == 0)
            {

                cout << "1)Id Grupo" << endl;
                cout << "2)Grado grupo"<< endl;
                cout << "3)Grupo(A, B, C)"<< endl;
                cout << "4)Nombre encargado"<< endl;
                cout << "5)Numero de alumnos"<< endl;
                cout << "6)Salon"<< endl;

                cout << "Que dato deseas modificar? ";
                cin >> op2;

                fflush(stdin);
                switch(op2)
                {
                    case 1:
                    cin.getline(con.idGrupo, 3);
                    break;

                    case 2:
                    cin.getline(con.grado, 3);
                    break;

                    case 3:
                    cin.getline(con.grupo, 3);
                    break;

                    case 4:
                    cin.getline(con.encargado, 50);
                    break;

                    case 5:
                    cin.getline(con.numAlumnos, 3);
                    break;

                    case 6:
                    cin.getline(con.salon, 10);
                    break;

                    default:
                        break;
                }
            }
            if(!mod.eof())
                temp.write((char*)&con, sizeof(con));
        }

        temp.close();
        mod.close();

        remove("Grupos.bin");
        rename("Temp.bin", "Grupos.bin");

        return;
    }

    archivo.close();
    cout << "Alumno no encontrado" << endl;
}

void Grupo::eliminar()
{
    ifstream archivo("Grupos.bin", ios::in);
    char idPago[4];
    int op, op2;

    if(!archivo.good())
    {
        cout << "Archivo no encontrado" << endl;
        return;
    }

    cout << "Ingrese el id del grupo a eliminar: " << endl;
    fflush(stdin);
    cin.getline(idPago, 4);

    Grupo con;

    while(!archivo.eof())
    {
        archivo.read((char*)&con, sizeof(con));

        if(!archivo.eof() && strcmp(con.idGrupo, idPago) == 0)
        {
            cout << "Id grupo: " << con.idGrupo << endl;
            cout << "Grado del grupo: " << con.grado << endl;
            cout << "Grupo (A,B,C): " << con.grupo << endl;
            cout << "Nombre encargado: " << con.encargado << endl;
            cout << "Numero de alumnos: " << con.numAlumnos << endl;
            cout << "Salon: " << con.salon << endl <<endl;

            cout << "Estas seguro que quieres eliminar este grupo (si == 1)? ";
            cin >> op;

            archivo.close();
        }
    }

    if(op == 1)
    {
        cout << "SI" << endl;
        ifstream mod("Grupos.bin", ios::in);
        ofstream temp("Temp.bin", ios::binary);

        if(!mod.good())
        {
            cout << "Archivo no encontrado" << endl;
            return;
        }

        while(!mod.eof())
        {
            mod.read((char*)&con, sizeof(con));
            if(!mod.eof() && strcmp(con.idGrupo, idPago) != 0)
            {
                temp.write((char*)&con, sizeof(con));
            }

        }

        temp.close();
        mod.close();

        remove("Grupos.bin");
        rename("Temp.bin", "Grupos.bin");

        return;
    }

    archivo.close();
    cout << "Grupo no encontrado" << endl;
}

void Grupo::generarIndice()
{
    if(!listaPag.empty()) {
        listaPag.clear();
        listaPares.clear();
    }

    obtenerInfo();
    LlenarArbol(listaPares);
    listaPag.sort(comparar);
    generarTXT(listaPag);
}

void Grupo::mostrarIndice()
{
    imprimList(listaPag);
    listaPag.clear();
    cout << endl;
}

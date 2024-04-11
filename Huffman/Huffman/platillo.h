#ifndef PLATILLO_H
#define PLATILLO_H
#include<iostream>
using namespace std;

class Platillo
{
public:
    Platillo();
    string getNombre() const;
    void setNombre(const string &value);

    string getDescrip() const;
    void setDescrip(const string &value);

    string getPrecio() const;
    void setPrecio(const string &value);

    string getCodigo() const;
    void setCodigo(const string &value);

    string getBandera() const;
    void setBandera(const string &value);

    friend ostream& operator <<(ostream &out,const Platillo &p){
        out<<p.getNombre() <<","
           <<p.getDescrip()<<","
           <<p.getPrecio() <<","
           <<p.getCodigo() <<","
           <<p.getBandera()<<",";
        return out;
    }
private:
    string nombre;
    string descrip;
    string precio;
    string codigo;
    string bandera;
};

#endif // PLATILLO_H

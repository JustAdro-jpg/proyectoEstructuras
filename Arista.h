#pragma once
#include <iostream>
#include <string>
using namespace std;

class Arista
{
private:
    string origen;
    string destino;

public:
    Arista()
    {
        origen = "";
        destino = "";
    }

    Arista(const string& o, const string& d)
    {
        origen = o;
        destino = d;
    }

    string getOrigen() const
    {
        return origen;
    }

    string getDestino() const
    {
        return destino;
    }

    void setOrigen(const string& o)
    {
        origen = o;
    }

    void setDestino(const string& d)
    {
        destino = d;
    }

    void mostrar() const
    {
        cout << "(" << origen << ", " << destino << ")";
    }
};

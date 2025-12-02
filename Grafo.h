#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  
#include <climits>   
#include "Arista.h"

using namespace std;

class Grafo
{
private:
    int nVertices;
    vector<Arista> aristas;

public:
    Grafo(int numVertices)
    {
        nVertices = numVertices;
    }

    void agregarArista(const string& o, const string& d)
    {
        aristas.emplace_back(o, d);
    }

    int getCantidadVertices() const
    {
        return nVertices;
    }

    int getCantidadAristas() const
    {
        return (int)aristas.size();
    }

    void mostrarAristas() const
    {
        cout << "Aristas del grafo:\n";
        for (int i = 0; i < (int)aristas.size(); ++i)
        {
            cout << i << ": ";
            aristas[i].mostrar();
            cout << "\n";
        }
    }

    int obtenerIndiceAristaAleatoria() const
    {
        if (aristas.empty()) {
            return -1;
        }
        return rand() % (int)aristas.size();
    }

    void eliminarAutociclos()
    {
        int k = 0;
        for (int i = 0; i < (int)aristas.size(); ++i)
        {
            if (aristas[i].getOrigen() != aristas[i].getDestino())
            {
                aristas[k] = aristas[i];
                k++;
            }
        }
        aristas.resize(k);
    }

    void contraerArista(int indice)
    {
        if (indice >= 0 && indice < (int)aristas.size()) {
            string u = aristas[indice].getOrigen();
            string v = aristas[indice].getDestino();
        
            for (int i = 0; i < (int)aristas.size(); ++i)
            {
                if (aristas[i].getOrigen() == v)
                    aristas[i].setOrigen(u);
                if (aristas[i].getDestino() == v)
                    aristas[i].setDestino(u);
            }
            eliminarAutociclos();
            nVertices--;
        }
    }

    int karger() const
    {
        Grafo g = *this;
        while (g.nVertices > 2)
        {
            int indice = g.obtenerIndiceAristaAleatoria();
            if (indice == -1) {
                break;
            }
            g.contraerArista(indice);
        }
        return (int)g.aristas.size();
    }

    int repetirKarger(int repeticiones) const
    {
        int mejor = INT_MAX;
        for (int i = 0; i < repeticiones; ++i)
        {
            int corte = karger();
            if (corte < mejor)
            {
                mejor = corte;
            }
        }
        return mejor;
    }
};

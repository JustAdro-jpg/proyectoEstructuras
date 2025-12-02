#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>   // rand
#include <climits>   // INT_MAX
#include "Arista.h"

using namespace std;

class Grafo
{
private:
    int nVertices;          // cantidad de vertices distintos (ciudades)
    vector<Arista> aristas; // SIN punteros, SIN new/delete

public:
    // Constructor: recibimos cantidad de vertices distintos
    Grafo(int numVertices)
    {
        nVertices = numVertices;
    }

    void agregarArista(const string& o, const string& d)
    {
        aristas.emplace_back(o, d); // crea Arista(o,d) al final
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

    // Devuelve el índice de una arista elegida al azar
    int obtenerIndiceAristaAleatoria() const
    {
        if (aristas.empty())
            return -1;
        int indice = rand() % aristas.size();
        return indice;
    }

    // Eliminar autociclos (aristas (u,u))
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

    // Contraer una arista: fusionar sus dos vertices
    void contraerArista(int indice)
    {
        if (indice < 0 || indice >= (int)aristas.size())
            return;

        string u = aristas[indice].getOrigen();
        string v = aristas[indice].getDestino();

        if (u == v)
            return; // ya era autociclo

        // Reemplazar todas las apariciones de v por u
        for (int i = 0; i < (int)aristas.size(); ++i)
        {
            if (aristas[i].getOrigen() == v)
                aristas[i].setOrigen(u);
            if (aristas[i].getDestino() == v)
                aristas[i].setDestino(u);
        }

        // Eliminar las aristas internas (autociclos) del nuevo supervertice
        eliminarAutociclos();

        // Hemos fusionado v dentro de u, por lo que hay un vertice menos
        nVertices--;
    }

    // Una sola ejecución de Karger
    int ejecutarKargerUnaVez() const
    {
        // 👇 Este es el punto clave:
        // Grafo g = *this crea una COPIA profunda del vector de aristas,
        // porque vector se copia por valor.
        Grafo g = *this;

        while (g.nVertices > 2)
        {
            int idx = g.obtenerIndiceAristaAleatoria();
            if (idx == -1)
                break;

            g.contraerArista(idx);
        }

        // Cuando quedan 2 supervertices, todas las aristas restantes cruzan el corte
        return (int)g.aristas.size();
    }

    // Ejecutar Karger varias veces para aumentar la probabilidad de encontrar el verdadero corte mínimo
    int ejecutarKargerVariasVeces(int repeticiones) const
    {
        int mejor = INT_MAX;

        for (int i = 0; i < repeticiones; ++i)
        {
            int corte = ejecutarKargerUnaVez();
            if (corte < mejor)
            {
                mejor = corte;
            }
        }

        return mejor;
    }
};

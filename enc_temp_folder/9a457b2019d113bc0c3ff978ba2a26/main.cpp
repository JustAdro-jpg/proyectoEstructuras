#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <set>
#include "Hash.h"
#include "Lista8.h"
#include "Caja.h"
#include "Arista.h"
#include "Grafo.h"

using namespace std;

Grafo* cargarGrafoDesdeArchivo(const string& nombreArchivo)
{
    ifstream in(nombreArchivo.c_str());
    if (!in)
    {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return nullptr;
    }

    Hash hashVertices;
    Lista8<Arista> listaAristas;

    int cantidadVertices = 0;
    int cantidadAristas = 0;

    set<pair<string, string>> aristasVistas;

    string linea;

    while (getline(in, linea))
    {
        if (linea.empty())
            continue;

        stringstream ss(linea);
        string nombreOrigen;

        if (!(ss >> nombreOrigen))
            continue;

        if (!hashVertices.buscar(nombreOrigen))
        {
            hashVertices.insertar(nombreOrigen);
            cantidadVertices++;
        }

        string nombreDestino;
        while (ss >> nombreDestino)
        {
            if (nombreDestino == "-1")
                break;

            if (!hashVertices.buscar(nombreDestino))
            {
                hashVertices.insertar(nombreDestino);
                cantidadVertices++;
            }

            string a = nombreOrigen;
            string b = nombreDestino;
            if (b < a) std::swap(a, b); 

            pair<string, string> clave = { a, b };

            auto res = aristasVistas.insert(clave);
            if (res.second)
            {
                Arista ar(a, b);      
                listaAristas.insertarFin(ar);
                cantidadAristas++;
            }
        }
    }

    cout << "\nGrafo cargado desde: " << nombreArchivo << endl;
    cout << "Cantidad de vertices (nombres distintos): " << cantidadVertices << endl;
    cout << "Cantidad de aristas (sin duplicados): " << cantidadAristas << endl;

    Grafo* g = new Grafo(cantidadVertices);

    Caja<Arista>* p = listaAristas.getPri();
    while (p != nullptr)
    {
        Arista a = p->getElemento();
        g->agregarArista(a.getOrigen(), a.getDestino());
        p = p->getSiguiente();
    }

    return g;
}

int main()
{
    srand((unsigned)time(NULL));

    int opcionArchivo;
    string nombreArchivo;

    cout << "Seleccione el archivo a usar:\n";
    cout << "1) Min_Cut_NOMBRES Prueba.txt\n";
    cout << "2) MIN_CUT_CON_NOMBRES.txt\n";
    cout << "Opcion: ";
    cin >> opcionArchivo;

    if (opcionArchivo == 1)
    {
        nombreArchivo = "Min_Cut_NOMBRES Prueba.txt";
    }
    else if (opcionArchivo == 2)
    {
        nombreArchivo = "MIN_CUT_CON_NOMBRES.txt";
    }
    else
    {
        cout << "Opcion invalida.\n";
        return 0;
    }

    Grafo* grafo = cargarGrafoDesdeArchivo(nombreArchivo);
    if (grafo == nullptr)
    {
        cout << "No se pudo construir el grafo.\n";
        return 0;
    }

    cout << "\n--- Informacion del grafo ---\n";
    cout << "Vertices: " << grafo->getCantidadVertices() << endl;
    cout << "Aristas: " << grafo->getCantidadAristas() << endl;

    int repeticiones = 212000;
    int mejorCorte = grafo->ejecutarKargerVariasVeces(repeticiones);

    cout << "\nResultado de Karger (" << repeticiones << " repeticiones):\n";
    cout << "Corte minimo estimado = " << mejorCorte << endl;

    delete grafo;
    return 0;
}
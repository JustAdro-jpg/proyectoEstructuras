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

Grafo* cargarGrafo(const string& nombreArchivo)
{
    ifstream in(nombreArchivo.c_str());
    if (!in)
    {
        return nullptr;
    }

    Hash hashVertices;
    Lista8<Arista> listaAristas;

    int cantidadVertices = 0;

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
            }
        }
    }

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

    int op;
    string archivo;

    cout << "Seleccione el archivo a usar:\n";
    cout << "1) Min_Cut_NOMBRES Prueba.txt\n";
    cout << "2) MIN_CUT_CON_NOMBRES.txt\n";
    cin >> op;

    if (op == 1)
    {
        archivo = "Min_Cut_NOMBRES Prueba.txt";
    }
    else if (op == 2)
    {
        archivo = "MIN_CUT_CON_NOMBRES.txt";
    }

    Grafo* grafo = cargarGrafo(archivo);
    if (grafo == nullptr)
    {
        cout << "No se pudo construir el grafo.\n";
        return 0;
    }

    cout << "\n--- Informacion del grafo ---\n";
    cout << "Vertices: " << grafo->getCantidadVertices() << endl;
    cout << "Aristas: " << grafo->getCantidadAristas() << endl;

    int repeticiones = 50000;
    int mejorCorte = grafo->repetirKarger(repeticiones);

    cout << "\nResultado de Karger (" << repeticiones << " repeticiones):\n";
    cout << "Corte minimo estimado = " << mejorCorte << endl;

    delete grafo;
    return 0;
}
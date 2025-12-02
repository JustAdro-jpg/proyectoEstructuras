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
    if (in)
    {
        Hash hashVertices;
        Lista8<Arista> listaAristas;
        int cantidadVertices = 0;
        set<pair<string, string>> aristasVistas;

        string linea;
        while (getline(in, linea))
        {
            stringstream ss(linea);
            string origen;
            ss >> origen;
            if (!hashVertices.buscar(origen))
            {
                hashVertices.insertar(origen);
                cantidadVertices++;
            }
            string destino;
            while ((ss >> destino) && (destino != "-1"))
            {
                if (!hashVertices.buscar(destino))
                {
                    hashVertices.insertar(destino);
                    cantidadVertices++;
                }

                string a = origen;
                string b = destino;
                if (b < a)
                {
                    string temp = a;
                    a = b;
                    b = temp;
                }

                pair<string, string> clave(a, b);
                if (aristasVistas.insert(clave).second)
                {
                    listaAristas.insertarFin(Arista(a, b));
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
    return nullptr;
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
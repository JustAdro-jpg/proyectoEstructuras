#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Lista8.h"

using namespace std;

class Hash
{
private:
    static const int TAM = 30011;
    Lista8<string> tabla[TAM];

    int fHash(const string nom)
    {
        int pos = 0;
        for (int i = 0; i < (int)nom.length(); i++)
        {
            int p2 = (int)pow(2, i);
            pos += (int)nom[i] * p2;
        }
        pos = pos % TAM;
        return abs(pos);
    }

    int fHashMultiplicacion(const string nom)
    {
        int Elem = 0;
        for (int i = 0; i < (int)nom.size(); i++)
        {
            Elem = Elem * 131 + (int)nom[i];
        }

        double A = (sqrt(5.0) - 1.0) / 2.0;
        double Mult = (double)Elem * A;
        double piso = floor(Mult);
        double fraccion = Mult - piso;
        int pos = (int)floor(fraccion * TAM);

        return abs(pos);
    }

public:
    Hash()
    {
    }

    void insertar(const string nombre)
    {
        int i = fHash(nombre);
        if (!tabla[i].buscarSecuencial(nombre))
        {
            tabla[i].insertarFin(nombre);
        }
    }

    void insertarCont(const string nombre)
    {
        int i = fHash(nombre);
        Caja<string>* ptr = tabla[i].buscarPtr(nombre);

        if (ptr != nullptr)
        {
            ptr->incrementar();
        }
        else
        {
            tabla[i].insertarFin(nombre);
        }
    }

    void insertarContMult(const string nombre)
    {
        int i = fHashMultiplicacion(nombre);
        Caja<string>* ptr = tabla[i].buscarPtr(nombre);

        if (ptr != nullptr)
        {
            ptr->incrementar();
        }
        else
        {
            tabla[i].insertarFin(nombre);
        }
    }

    bool eliminar(const string nombre)
    {
        int i = fHash(nombre);
        return tabla[i].eliminarDado(nombre);
    }

    bool buscar(const string nombre)
    {
        int i = fHash(nombre);
        return tabla[i].buscarSecuencial(nombre);
    }

    void mostrarTablaCont()
    {
        cout << "\n=== TABLA HASH ===\n";
        for (int i = 0; i < TAM; ++i)
        {
            cout << "[" << i << "]: ";
            Caja<string>* p = tabla[i].getPri();
            while (p != nullptr)
            {
                cout << p->getElemento()
                    << "(" << p->getContador() << ") ";
                p = p->getSiguiente();
            }
            cout << "\n";
        }
    }

    void mostrarTabla()
    {
        cout << "\n=== TABLA HASH ===\n";
        for (int i = 0; i < TAM; ++i)
        {
            cout << "[" << i << "]: ";
            tabla[i].mostrar();
        }
    }

    void leerDesdeArchivo()
    {
        ifstream in("cien.txt");
        if (!in)
        {
            cout << "No se pudo abrir el archivo\n";
            return;
        }

        string linea;
        int count = 0;

        while (getline(in, linea))
        {
            if (!linea.empty())
            {
                insertarCont(linea);
                count++;
            }
        }

        cout << "Se insertaron " << count << " nombres.\n";
    }

    void leerDesdeArchivoCont()
    {
        ifstream in("cien.txt");
        if (!in)
        {
            cout << "No se pudo abrir el archivo\n";
            return;
        }

        string palabra;
        int count = 0;

        while (in >> palabra)
        {
            insertarCont(palabra);
            count++;
        }

        cout << "Se insertaron " << count << " palabras.\n";
    }

    void leerDesdeArchivoMult()
    {
        ifstream in("cien.txt");
        if (!in)
        {
            cout << "No se pudo abrir el archivo\n";
            return;
        }

        string palabra;
        int count = 0;

        while (in >> palabra)
        {
            insertarContMult(palabra);
            count++;
        }

        cout << "Se insertaron " << count << " palabras.\n";
    }

    //Para corte minimo
    // Inserta nombre si no existe y devuelve el puntero a la Caja.
    // esNuevo = true si se acaba de insertar; false si ya existía.
    Caja<string>* insertarYRetornar(const string nombre, bool& esNuevo)
    {
        int i = fHash(nombre);
        Caja<string>* ptr = tabla[i].buscarPtr(nombre);

        if (ptr != nullptr)
        {
            esNuevo = false;
            return ptr;
        }
        else
        {
            tabla[i].insertarFin(nombre);
            ptr = tabla[i].buscarPtr(nombre); // nodo recien insertado
            esNuevo = true;
            return ptr;
        }
    }

    void menu()
    {
        int op;
        string nombre;

        do
        {
            cout << "\n====== MENU HASH ======\n";
            cout << "1) Insertar nombre\n";
            cout << "2) Eliminar nombre\n";
            cout << "3) Buscar nombre\n";
            cout << "4) Mostrar la Tabla Hash\n";
            cout << "5) Leer nombres de un archivo\n";
            cout << "6) Multiplicacion\n";
            cout << "0) Salir\n";
            cout << "Opcion: ";
            cin >> op;
            cin.ignore();

            switch (op)
            {
            case 1:
                cout << "Nombre: ";
                getline(cin, nombre);
                insertar(nombre);
                break;
            case 2:
                cout << "Nombre: ";
                getline(cin, nombre);
                if (eliminar(nombre))
                {
                    cout << "Eliminado.\n";
                }
                else
                {
                    cout << "No existe.\n";
                }
                break;
            case 3:
                cout << "Nombre: ";
                getline(cin, nombre);
                if (buscar(nombre))
                {
                    cout << "Si esta.\n";
                }
                else
                {
                    cout << "No se encontro.\n";
                }
                break;
            case 4:
                mostrarTablaCont();
                break;
            case 5:
                leerDesdeArchivoCont();
                break;
            case 6:
                fHashMultiplicacion(nombre);
                break;
            case 0:
                break;
            default:
                cout << "Opcion invalida.\n";
            }

        } while (op != 0);
    }
};

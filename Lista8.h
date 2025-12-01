#pragma once
#include <iostream>
#include "Caja.h"
using namespace std;

template <typename T>
class Lista8
{
private:
    Caja<T>* pri;
    Caja<T>* ult;

public:
    Lista8()
    {
        pri = nullptr;
        ult = nullptr;
    }

    bool insertarFin(const T& elem)
    {
        if (pri == nullptr)
        {
            pri = new Caja<T>(nullptr, elem, nullptr);
            ult = pri;
            return true;
        }
        else
        {
            Caja<T>* aux;
            ult = new Caja<T>(ult, elem, nullptr);
            aux = ult->getAnterior();
            aux->setSiguiente(ult);
            return true;
        }
    }

    bool insertarPrincipio(const T& elem)
    {
        if (pri == nullptr)
        {
            pri = new Caja<T>(nullptr, elem, nullptr);
            ult = pri;
            return true;
        }
        else
        {
            Caja<T>* aux;
            pri = new Caja<T>(nullptr, elem, pri);
            aux = pri->getSiguiente();
            aux->setAnterior(pri);
            return true;
        }
    }

    bool eliminarPrincipio()
    {
        bool res;
        if (pri == nullptr)
        {
            res = false;
        }
        else
        {
            if (pri == ult)
            {
                delete pri;
                pri = nullptr;
                ult = nullptr;
                res = true;
            }
            else
            {
                Caja<T>* aux = pri;
                pri = pri->getSiguiente();
                pri->setAnterior(nullptr);
                delete aux;
                res = true;
            }
        }

        return res;
    }

    bool eliminarFin()
    {
        bool res;
        if (ult == nullptr)
        {
            res = false; // lista vacía
        }
        else
        {
            if (pri == ult) // un solo nodo
            {
                delete ult;
                pri = nullptr;
                ult = nullptr;
                res = true;
            }
            else
            {
                Caja<T>* aux = ult;           // nodo a borrar
                ult = ult->getAnterior();     // nuevo último
                ult->setSiguiente(nullptr);   // extremo derecho limpio
                delete aux;                   // liberar memoria
                res = true;
            }
        }

        return res;
    }

    void mostrar() const
    {
        Caja<T>* p = pri;
        while (p != nullptr)
        {
            cout << p->getElemento() << " ";
            p = p->getSiguiente();
        }
        cout << endl;
    }

    bool eliminarDado(const T& el)
    {
        bool res = false;

        if (pri != nullptr)
        {
            Caja<T>* p = buscarPtr(el);

            if (p != nullptr)
            {
                if (p == pri)
                {
                    res = eliminarPrincipio();
                }
                else if (p == ult)
                {
                    res = eliminarFin();
                }
                else
                {
                    Caja<T>* ant = p->getAnterior();
                    Caja<T>* sig = p->getSiguiente();

                    ant->setSiguiente(sig);
                    sig->setAnterior(ant);

                    delete p;
                    res = true;
                }
            }
        }

        return res;
    }

    Caja<T>* buscarPtr(const T& el)
    {
        Caja<T>* aux = pri;
        Caja<T>* ptr = nullptr;
        while (aux != nullptr)
        {
            if (aux->getElemento() == el)
            {
                ptr = aux;
            }
            aux = aux->getSiguiente();
        }
        return ptr;
    }

    void eliminarTodo()
    {
        while (pri != nullptr)
        {
            eliminarPrincipio();
        }
    }

    bool buscarSecuencial(const T& el)
    {
        Caja<T>* aux = pri;
        while (aux != nullptr)
        {
            if (aux->getElemento() == el)
            {
                return true;
            }
            aux = aux->getSiguiente();
        }
        return false;
    }

    bool buscarRec(const T& el, Caja<T>* aux)
    {
        bool res;
        if (aux == nullptr)
        {
            res = false;
        }
        else
        {
            if (el == aux->getElemento())
            {
                res = true;
            }
            else
            {
                res = buscarRec(el, aux->getSiguiente());
            }
        }
        return res;
    }

    Caja<T>* getPri()
    {
        return pri;
    }

    void menu()
    {
        int opcion;
        T valor;
        bool continuar = true;

        while (continuar)
        {
            cout << "\n===== MENU LISTA8 =====\n";
            cout << "1. Insertar al principio\n";
            cout << "2. Insertar al final\n";
            cout << "3. Eliminar al principio\n";
            cout << "4. Eliminar al final\n";
            cout << "5. Mostrar lista\n";
            cout << "6. Buscar (secuencial)\n";
            cout << "7. Buscar (recursivo)\n";
            cout << "8. Eliminar Elemento Dado\n";
            cout << "9. Eliminar Todo\n";
            cout << "0. Salir\n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
            {
                cout << "Ingrese valor: ";
                cin >> valor;
                insertarPrincipio(valor);
                break;
            }
            case 2:
            {
                cout << "Ingrese valor: ";
                cin >> valor;
                insertarFin(valor);
                break;
            }
            case 3:
            {
                if (eliminarPrincipio())
                {
                    cout << "Eliminado correctamente.\n";
                }
                else
                {
                    cout << "La lista esta vacia.\n";
                }
                break;
            }
            case 4:
            {
                if (eliminarFin())
                {
                    cout << "Eliminado correctamente.\n";
                }
                else
                {
                    cout << "La lista esta vacia.\n";
                }
                break;
            }
            case 5:
            {
                cout << "Contenido de la lista: ";
                mostrar();
                break;
            }
            case 6:
            {
                cout << "Ingrese valor a buscar: ";
                cin >> valor;
                if (buscarSecuencial(valor))
                {
                    cout << "Elemento encontrado.\n";
                }
                else
                {
                    cout << "No se encontro.\n";
                }
                break;
            }
            case 7:
            {
                cout << "Ingrese valor a buscar: ";
                cin >> valor;
                if (buscarRec(valor, pri))
                {
                    cout << "Elemento encontrado.\n";
                }
                else
                {
                    cout << "No se encontro.\n";
                }
                break;
            }
            case 8:
            {
                cout << "Ingrese valor a eliminar: ";
                cin >> valor;
                eliminarDado(valor);
                break;
            }
            case 9:
            {
                eliminarTodo();
                break;
            }
            case 0:
            {
                continuar = false;
                break;
            }
            default:
            {
                cout << "Opcion invalida.\n";
            }
            }
        }
    }
};

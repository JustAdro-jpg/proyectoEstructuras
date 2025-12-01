#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Caja
{
private:
    T el;
    Caja<T>* sig;
    Caja<T>* ant;
    int contador;

public:
    Caja()
    {
        sig = nullptr;
        ant = nullptr;
        contador = 1;
    }

    Caja(Caja<T>* anterior, const T& valor, Caja<T>* siguiente)
    {
        ant = anterior;
        el = valor;
        sig = siguiente;
        contador = 1;
    }

    T getElemento() const
    {
        return el;
    }

    Caja<T>* getSiguiente() const
    {
        return sig;
    }

    Caja<T>* getAnterior() const
    {
        return ant;
    }

    int getContador()
    {
        return contador;
    }

    void setElemento(const T& v)
    {
        el = v;
    }

    void setSiguiente(Caja<T>* p)
    {
        sig = p;
    }

    void setAnterior(Caja<T>* p)
    {
        ant = p;
    }

    void incrementar()
    {
        contador++;
    }

    void setContador(int c)
    {
        contador = c;
    }
};

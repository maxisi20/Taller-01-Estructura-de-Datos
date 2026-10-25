#ifndef ESTRUCTURAS_HPP
#define ESTRUCTURAS_HPP

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Nodo {
private:
    T dato;
    Nodo<T>* siguiente;
public:
    Nodo(T dato) {
        this->dato = dato;
        this->siguiente = nullptr;
    }
    T getDato() { return dato; }
    Nodo<T>* getSiguiente() { return siguiente; }
    void setSiguiente(Nodo<T>* nuevo) { this->siguiente = nuevo; }
};

template <typename T>
class Lista {
private:
    Nodo<T>* head;
    int largo;
public:
    Lista() {
        this->head = nullptr;
        this->largo = 0;
    }
    ~Lista() {
        Nodo<T>* actual = this->head;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
    }

    Nodo<T>* getUltimo() {
        Nodo<T>* aux = this->head;
        if (aux == nullptr) return nullptr;
        while (aux->getSiguiente() != nullptr) {
            aux = aux->getSiguiente();
        }
        return aux;
    }
    
    void añadir(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (this->head == nullptr) {
            this->head = nuevo;
        } else {
            Nodo<T>* ultimo = getUltimo();
            ultimo->setSiguiente(nuevo);
        }
        this->largo++;
    }
    
    int getSize() {
        return this->largo;
    }
    
    T getIndice(int indice) {
        Nodo<T>* aux = head;
        int cont = 0;
        while (aux != nullptr) {
            if (indice == cont) {
                return aux->getDato();
            }
            aux = aux->getSiguiente();
            cont++;
        }
        return nullptr; 
    }
    
    string toString() {
        string salida = "";
        Nodo<T>* aux = head;
        while (aux != nullptr) {
            salida += aux->getDato()->toString();
            aux = aux->getSiguiente();
        }
        return salida;
    }
    
    T extraerPrimero() {
        if (this->head == nullptr) return nullptr;
        Nodo<T>* nodoEliminar = this->head;
        this->head = this->head->getSiguiente();
        T dato = nodoEliminar->getDato();
        delete nodoEliminar;
        this->largo--;
        return dato;
    }
};

template <typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* fin;
    int largo;

public:
    Cola() {
        this->frente = nullptr;
        this->fin = nullptr;
        this->largo = 0;
    }

    ~Cola() {
        while (!estaVacia()) {
            Nodo<T>* aux = this->frente;
            this->frente = this->frente->getSiguiente();
            delete aux;
        }
    }

    bool estaVacia() {
        return this->frente == nullptr;
    }

    void encolar(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        if (estaVacia()) {
            this->frente = nuevo;
            this->fin = nuevo;
        } else {
            this->fin->setSiguiente(nuevo);
            this->fin = nuevo;
        }
        this->largo++;
    }

    T desencolar() {
        if (estaVacia()) {
            return nullptr;
        }
        Nodo<T>* nodoAEliminar = this->frente;
        T dato = nodoAEliminar->getDato();
        
        this->frente = this->frente->getSiguiente();
        if (this->frente == nullptr) {
            this->fin = nullptr;
        }
        
        delete nodoAEliminar;
        this->largo--;
        return dato;
    }

    int getSize() {
        return this->largo;
    }

    T getFrente() {
        if (estaVacia()) return nullptr;
        return this->frente->getDato();
    }
};

#endif
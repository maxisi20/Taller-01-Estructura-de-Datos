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
#endif
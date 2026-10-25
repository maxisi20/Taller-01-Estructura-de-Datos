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

template <typename T>
class NodoArbol {
public:
    T dato;
    NodoArbol<T>* izq;
    NodoArbol<T>* der;
    int altura;

    NodoArbol(T dato) {
        this->dato = dato;
        this->izq = nullptr;
        this->der = nullptr;
        this->altura = 1;
    }
};

template <typename T>
class ArbolAVL {
private:
    NodoArbol<T>* raiz;

    int getAltura(NodoArbol<T>* nodo) {
        if (nodo == nullptr) return 0;
        return nodo->altura;
    }

    int maximo(int a, int b) {
        return (a > b) ? a : b;
    }

    int obtenerBalance(NodoArbol<T>* nodo) {
        if (nodo == nullptr) return 0;
        return getAltura(nodo->izq) - getAltura(nodo->der);
    }

    NodoArbol<T>* rotacionDerecha(NodoArbol<T>* y) {
        NodoArbol<T>* x = y->izq;
        NodoArbol<T>* T2 = x->der;

        x->der = y;
        y->izq = T2;

        y->altura = maximo(getAltura(y->izq), getAltura(y->der)) + 1;
        x->altura = maximo(getAltura(x->izq), getAltura(x->der)) + 1;

        return x;
    }

    NodoArbol<T>* rotacionIzquierda(NodoArbol<T>* x) {
        NodoArbol<T>* y = x->der;
        NodoArbol<T>* T2 = y->izq;

        y->izq = x;
        x->der = T2;

        x->altura = maximo(getAltura(x->izq), getAltura(x->der)) + 1;
        y->altura = maximo(getAltura(y->izq), getAltura(y->der)) + 1;

        return y;
    }

    NodoArbol<T>* insertarRecursivo(NodoArbol<T>* nodo, T dato) {
        if (nodo == nullptr)
            return new NodoArbol<T>(dato);

        if (dato->getId() < nodo->dato->getId())
            nodo->izq = insertarRecursivo(nodo->izq, dato);
        else if (dato->getId() > nodo->dato->getId())
            nodo->der = insertarRecursivo(nodo->der, dato);
        else
            return nodo;

        nodo->altura = 1 + maximo(getAltura(nodo->izq), getAltura(nodo->der));
        int balance = obtenerBalance(nodo);

        if (balance > 1 && dato->getId() < nodo->izq->dato->getId())
            return rotacionDerecha(nodo);
        if (balance < -1 && dato->getId() > nodo->der->dato->getId())
            return rotacionIzquierda(nodo);
        if (balance > 1 && dato->getId() > nodo->izq->dato->getId()) {
            nodo->izq = rotacionIzquierda(nodo->izq);
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && dato->getId() < nodo->der->dato->getId()) {
            nodo->der = rotacionDerecha(nodo->der);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    NodoArbol<T>* nodoMinimo(NodoArbol<T>* nodo) {
        NodoArbol<T>* actual = nodo;
        while (actual->izq != nullptr)
            actual = actual->izq;
        return actual;
    }

    NodoArbol<T>* eliminarRecursivo(NodoArbol<T>* nodo, int id) {
        if (nodo == nullptr) return nodo;

        if (id < nodo->dato->getId())
            nodo->izq = eliminarRecursivo(nodo->izq, id);
        else if (id > nodo->dato->getId())
            nodo->der = eliminarRecursivo(nodo->der, id);
        else {
            if ((nodo->izq == nullptr) || (nodo->der == nullptr)) {
                NodoArbol<T>* temp = nodo->izq ? nodo->izq : nodo->der;
                if (temp == nullptr) {
                    temp = nodo;
                    nodo = nullptr;
                } else {
                    *nodo = *temp; 
                }
                delete temp;
            } else {
                NodoArbol<T>* temp = nodoMinimo(nodo->der);
                nodo->dato = temp->dato;
                nodo->der = eliminarRecursivo(nodo->der, temp->dato->getId());
            }
        }

        if (nodo == nullptr) return nodo;

        nodo->altura = 1 + maximo(getAltura(nodo->izq), getAltura(nodo->der));
        int balance = obtenerBalance(nodo);

        if (balance > 1 && obtenerBalance(nodo->izq) >= 0)
            return rotacionDerecha(nodo);
        if (balance > 1 && obtenerBalance(nodo->izq) < 0) {
            nodo->izq = rotacionIzquierda(nodo->izq);
            return rotacionDerecha(nodo);
        }
        if (balance < -1 && obtenerBalance(nodo->der) <= 0)
            return rotacionIzquierda(nodo);
        if (balance < -1 && obtenerBalance(nodo->der) > 0) {
            nodo->der = rotacionDerecha(nodo->der);
            return rotacionIzquierda(nodo);
        }

        return nodo;
    }

    NodoArbol<T>* buscarRecursivo(NodoArbol<T>* nodo, int id) {
        if (nodo == nullptr || nodo->dato->getId() == id)
            return nodo;

        if (nodo->dato->getId() < id)
            return buscarRecursivo(nodo->der, id);

        return buscarRecursivo(nodo->izq, id);
    }

    void inOrden(NodoArbol<T>* nodo) {
        if (nodo != nullptr) {
            inOrden(nodo->izq);
            cout << "ID: " << nodo->dato->getId() << " - Nombre: " << nodo->dato->getNombre() << endl;
            inOrden(nodo->der);
        }
    }

    void vaciarArbol(NodoArbol<T>* nodo) {
        if (nodo != nullptr) {
            vaciarArbol(nodo->izq);
            vaciarArbol(nodo->der);
            delete nodo; 
        }
    }

public:
    ArbolAVL() { this->raiz = nullptr; }

    ~ArbolAVL() {
        vaciarArbol(raiz);
    }

    void insertar(T dato) {
        raiz = insertarRecursivo(raiz, dato);
    }

    void eliminar(int id) {
        raiz = eliminarRecursivo(raiz, id);
    }

    T buscar(int id) {
        NodoArbol<T>* resultado = buscarRecursivo(raiz, id);
        if (resultado != nullptr) return resultado->dato;
        return nullptr;
    }

    void mostrarInOrden() {
        if (raiz == nullptr) {
            cout << "No hay pacientes registrados." << endl;
            return;
        }
        inOrden(raiz);
    }
};

#endif
#ifndef ESTRUCTURAS_HPP
#define ESTRUCTURAS_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include "Paciente.hpp"

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
	T getDato() {
		return dato;
	}
	Nodo<T>* getSiguiente() {
		return siguiente;
	}
	void setSiguiente(Nodo<T>* nuevo) {
		this->siguiente = nuevo;
	}
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

	void anadir(T dato) {
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
			delete nodo->dato;   
			delete nodo;
		}
	}
	
	int contarNodos(NodoArbol<T>* nodo) {
        if (nodo == nullptr) return 0;
        return 1 + contarNodos(nodo->izq) + contarNodos(nodo->der);
    }
    	void preOrden(NodoArbol<T>* nodo) {
		if (nodo != nullptr) {
			cout << "ID: " << nodo->dato->getId() << " - Nombre: " << nodo->dato->getNombre() << endl;
			preOrden(nodo->izq);
			preOrden(nodo->der);
		}
	}

	void postOrden(NodoArbol<T>* nodo) {
		if (nodo != nullptr) {
			postOrden(nodo->izq);
			postOrden(nodo->der);
			cout << "ID: " << nodo->dato->getId() << " - Nombre: " << nodo->dato->getNombre() << endl;
		}
	}

	void balances(NodoArbol<T>* nodo) {
		if (nodo != nullptr) {
			balances(nodo->izq);
			cout << "ID: " << nodo->dato->getId() << " - Altura: " << nodo->altura
			     << " - Factor de balance: " << obtenerBalance(nodo) << endl;
			balances(nodo->der);
		}
	}

	T buscarNombreRec(NodoArbol<T>* nodo, string nombre) {
		if (nodo == nullptr) return nullptr;
		if (nodo->dato->getNombre() == nombre) return nodo->dato;
		T r = buscarNombreRec(nodo->izq, nombre);
		if (r != nullptr) return r;
		return buscarNombreRec(nodo->der, nombre);
	}


public:
	ArbolAVL() {
		this->raiz = nullptr;
	}

	~ArbolAVL() {
		vaciarArbol(raiz);
	}


	bool insertar(T dato) {
		if (buscar(dato->getId()) != nullptr) return false;
		raiz = insertarRecursivo(raiz, dato);
		return true;
	}

	void eliminar(int id) {
		T dato = buscar(id);
		if (dato == nullptr) return;
		raiz = eliminarRecursivo(raiz, id);
		delete dato;
	}

	T buscarConRuta(int id, string& ruta) {
		ruta = "";
		NodoArbol<T>* actual = raiz;
		while (actual != nullptr) {
			if (ruta != "") ruta += " -> ";
			ruta += to_string(actual->dato->getId());
			if (actual->dato->getId() == id) return actual->dato;
			if (id < actual->dato->getId()) actual = actual->izq;
			else actual = actual->der;
		}
		return nullptr;
	}

	T buscarPorNombre(string nombre) {
		return buscarNombreRec(raiz, nombre);
	}

	void mostrarPreOrden() {
		if (raiz == nullptr) { cout << "No hay pacientes registrados." << endl; return; }
		preOrden(raiz);
	}

	void mostrarPostOrden() {
		if (raiz == nullptr) { cout << "No hay pacientes registrados." << endl; return; }
		postOrden(raiz);
	}

	void mostrarBalances() {
		if (raiz == nullptr) { cout << "No hay pacientes registrados." << endl; return; }
		balances(raiz);
	}

	int getAltura() {
		return getAltura(raiz);
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
	
	int getSize() {
        return contarNodos(raiz);
    }
};

class NodoDecision {
public:
	bool esHoja;
	string atributo;
	string op;
	double valor;
	string valorTexto;
	string servicio;
	NodoDecision* si;
	NodoDecision* no;

	NodoDecision(string servicio) {
		this->esHoja = true;
		this->atributo = "";
		this->op = "";
		this->valor = 0;
		this->valorTexto = "";
		this->servicio = servicio;
		this->si = nullptr;
		this->no = nullptr;
	}

	NodoDecision(string atributo, string op, double valor) {
		this->esHoja = false;
		this->atributo = atributo;
		this->op = op;
		this->valor = valor;
		this->valorTexto = "";
		this->servicio = "";
		this->si = nullptr;
		this->no = nullptr;
	}
	
	NodoDecision(string atributo, string op, string valorTexto) {
		this->esHoja = false;
		this->atributo = atributo;
		this->op = op;
		this->valor = 0;
		this->valorTexto = valorTexto;
		this->servicio = "";
		this->si = nullptr;
		this->no = nullptr;
	}

	string textoValor() {
		if (valorTexto != "") return valorTexto;
		string s = to_string(valor);
		while (s.back() == '0') s.pop_back();
		if (s.back() == '.') s.pop_back();
		return s;
	}

	string pregunta() {
		if (esHoja) return "Servicio: " + servicio;
		return atributo + " " + op + " " + textoValor();
	}

	string negacion() {
		if (esHoja) return "Servicio: " + servicio;
		string opNegado = (op == "<") ? ">=" : (op == ">=") ? "<" : "!=";
		return atributo + " " + opNegado + " " + textoValor();
	}
};

class ArbolDecision {
private:
	NodoDecision* raiz;

	void construir() {
		NodoDecision* dias = new NodoDecision("DiasHospitalizacion", ">=", 2.0);
		dias->si = new NodoDecision("Hospitalizacion");
		dias->no = new NodoDecision("Medicina General");

		NodoDecision* presion = new NodoDecision("PresionArterial", ">=", 180.0);
		presion->si = new NodoDecision("Cardiologia");
		presion->no = dias;

		NodoDecision* pecho = new NodoDecision("TipoDolor", "==", string("pecho"));
		pecho->si = new NodoDecision("Cardiologia");
		pecho->no = presion;

		NodoDecision* cirugia = new NodoDecision("RequiereCirugia", "==", 1.0);
		cirugia->si = new NodoDecision("Cirugia");
		cirugia->no = pecho;

		NodoDecision* neuro = new NodoDecision("SintomasNeurologicos", "==", 1.0);
		neuro->si = new NodoDecision("Neurologia");
		neuro->no = cirugia;

		NodoDecision* cirTrauma = new NodoDecision("RequiereCirugia", "==", 1.0);
		cirTrauma->si = new NodoDecision("Cirugia");
		cirTrauma->no = new NodoDecision("Traumatologia");

		NodoDecision* trauma = new NodoDecision("Trauma", "==", 1.0);
		trauma->si = cirTrauma;
		trauma->no = neuro;

		NodoDecision* temp = new NodoDecision("Temperatura", ">=", 39.5);
		temp->si = new NodoDecision("Urgencias");
		temp->no = trauma;

		NodoDecision* dolor = new NodoDecision("Dolor", ">=", 8.0);
		dolor->si = new NodoDecision("Urgencias");
		dolor->no = temp;

		NodoDecision* edad = new NodoDecision("Edad", "<", 14.0);
		edad->si = new NodoDecision("Pediatria");
		edad->no = dolor;

		this->raiz = edad;
	}

	string normalizar(string texto) {
		string r = "";
		for (size_t i = 0; i < texto.size(); i++) {
			char c = texto[i];
			if (c == ' ' || c == '\r' || c == '\n') continue;
			if (c >= 'A' && c <= 'Z') c = c + ('a' - 'A');
			r += c;
		}
		return r;
	}

	double valorNumerico(Paciente* p, string atributo) {
		if (atributo == "Edad") return p->getEdad();
		if (atributo == "Temperatura") return p->getTemperatura();
		if (atributo == "PresionArterial") return p->getPresionArterial();
		if (atributo == "Dolor") return p->getDolor();
		if (atributo == "Trauma") return p->getTrauma();
		if (atributo == "SintomasNeurologicos") return p->getSintomasNeurologicos();
		if (atributo == "RequiereCirugia") return p->getRequiereCirugia();
		if (atributo == "DiasHospitalizacion") return p->getDiasHospitalizacion();
		
		throw invalid_argument("Atributo desconocido en el arbol de decision: " + atributo);
	}

	bool cumple(NodoDecision* nodo, Paciente* p) {
		if (nodo->atributo == "TipoDolor")
			return normalizar(p->getTipoDolor()) == nodo->valorTexto;
		double x = valorNumerico(p, nodo->atributo);
		if (nodo->op == "<") return x < nodo->valor;
		if (nodo->op == ">=") return x >= nodo->valor;
		return x == nodo->valor;
	}

	void liberar(NodoDecision* nodo) {
		if (nodo == nullptr) return;
		liberar(nodo->si);
		liberar(nodo->no);
		delete nodo;
	}

	void preordenRec(NodoDecision* nodo, int nivel) {
		if (nodo == nullptr) return;
		cout << string(nivel * 2, ' ') << "- " << nodo->pregunta() << endl;
		preordenRec(nodo->si, nivel + 1);
		preordenRec(nodo->no, nivel + 1);
	}
	void inordenRec(NodoDecision* nodo, int nivel) {
		if (nodo == nullptr) return;
		inordenRec(nodo->si, nivel + 1);
		cout << string(nivel * 2, ' ') << "- " << nodo->pregunta() << endl;
		inordenRec(nodo->no, nivel + 1);
	}
	void postordenRec(NodoDecision* nodo, int nivel) {
		if (nodo == nullptr) return;
		postordenRec(nodo->si, nivel + 1);
		postordenRec(nodo->no, nivel + 1);
		cout << string(nivel * 2, ' ') << "- " << nodo->pregunta() << endl;
	}

public:
	ArbolDecision() { this->raiz = nullptr; construir(); }
	~ArbolDecision() { liberar(raiz); }

	bool validar(Paciente* p, string& motivo) {
		if (p == nullptr) { motivo = "Paciente nulo"; return false; }
		if (p->getId() <= 0) { motivo = "ID invalido"; return false; }
		if (p->getNombre().empty()) { motivo = "Nombre vacio (datos insuficientes)"; return false; }
		if (p->getEdad() < 0 || p->getEdad() > 120) { motivo = "Edad fuera de rango (0-120)"; return false; }
		if (p->getTemperatura() < 30.0 || p->getTemperatura() > 45.0) { motivo = "Temperatura fuera de rango (30-45)"; return false; }
		if (p->getPresionArterial() < 50 || p->getPresionArterial() > 260) { motivo = "Presion fuera de rango (50-260)"; return false; }
		if (p->getDolor() < 0 || p->getDolor() > 10) { motivo = "Dolor fuera de rango (0-10)"; return false; }
		string td = normalizar(p->getTipoDolor());
		if (td != "pecho" && td != "cabeza" && td != "abdomen" && td != "extremidad" && td != "otro") {
			motivo = "TipoDolor desconocido"; return false;
		}
		int t = p->getTrauma(), s = p->getSintomasNeurologicos(), c = p->getRequiereCirugia();
		if ((t != 0 && t != 1) || (s != 0 && s != 1) || (c != 0 && c != 1)) {
			motivo = "Trauma/SintomasNeurologicos/RequiereCirugia deben ser 0 o 1"; return false;
		}
		if (p->getDiasHospitalizacion() < 0 || p->getDiasHospitalizacion() > 365) {
			motivo = "DiasHospitalizacion fuera de rango (0-365)"; return false;
		}
		return true;
	}
	string clasificar(Paciente* p, string& ruta) {
		string motivo = "";
		if (!validar(p, motivo)) { ruta = motivo; return ""; }
		ruta = "";
		NodoDecision* actual = raiz;
		while (!actual->esHoja) {
			bool resultado = cumple(actual, p);
			if (ruta != "") ruta += " -> ";
			ruta += resultado ? actual->pregunta() : actual->negacion();
			actual = resultado ? actual->si : actual->no;
		}
		return actual->servicio;
	}

	void preorden()  { cout << "=== Arbol de decision (preorden) ===" << endl;  preordenRec(raiz, 0); }
	void inorden()   { cout << "=== Arbol de decision (inorden) ===" << endl;   inordenRec(raiz, 0); }
	void postorden() { cout << "=== Arbol de decision (postorden) ===" << endl; postordenRec(raiz, 0); }
};
#endif
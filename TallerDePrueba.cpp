#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "Paciente.cpp"

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

class Departamento {
protected:
    Lista<Paciente*>* suLista; 
    string nombre;
public:
    Departamento(string nombre) {
        this->nombre = nombre;
        this->suLista = new Lista<Paciente*>();
    }
    void agregarPaciente(Paciente* paciente){
        suLista->añadir(paciente);
    }
    string getNombre() {
        return nombre;
    }
    string toString() {
        return this->nombre + "\n";
    }
    virtual void mostrarEstado() = 0;
};

class Urgencias : public Departamento {
public:
    Urgencias() : Departamento("Urgencias") {}
    
    void mostrarEstado() {
        cout << "--- Estado Urgencias ---"<<endl;
        cout << "Pacientes en urgencias: " << this->suLista->getSize() << endl;
        cout << this->suLista->toString();
    }
};
class MedicinaGen : public Departamento {
public:
    MedicinaGen() : Departamento("Medicina General") {}
    
    void mostrarEstado() {
        cout << "--- Estado Medicina General ---"<<endl;
        cout << "Pacientes en Medicina General: " << this->suLista->getSize() << endl;
        cout << this->suLista->toString();
    }
};
class Cardiologia : public Departamento {
public:
    Cardiologia() : Departamento("Cardiologia") {}
    
    void mostrarEstado() {
        cout << "--- Estado Cardiologia ---"<<endl;
        cout << "Pacientes en Cardiologia: " << this->suLista->getSize() << endl;
        cout << this->suLista->toString();
    }
};
class Neurología : public Departamento {
public:
    Neurología() : Departamento("Neurología") {}
    
    void mostrarEstado() {
        cout << "--- Estado Neurología ---"<<endl;
        cout << "Pacientes en Neurología: " << this->suLista->getSize() << endl;
        cout << this->suLista->toString();
    }
};
class Traumatologia : public Departamento {
public:
    Traumatologia() : Departamento("Traumatologia") {}
    
    void mostrarEstado() {
        cout << "--- Estado Traumatologia ---"<<endl;
        cout << "Pacientes en Traumatologia: " << this->suLista->getSize() << endl;
        cout << this->suLista->toString();
    }
};
class Cirugia : public Departamento {
public:
    Cirugia() : Departamento("Cirugia") {}
    
    void mostrarEstado() {
        cout << "--- Estado Cirugia ---"<<endl;
        cout<< "Pacientes en Cirugia: " << this->suLista->getSize() << endl;
        cout << this->suLista->toString();
    }
};
class Pediatria : public Departamento {
public:
    Pediatria() : Departamento("Pediatria") {}
    
    void mostrarEstado() {
        cout << "--- Estado Pediatria ---"<<endl;
        cout << "Pacientes en Pediatria: " << this->suLista->getSize() << endl;
        cout << this->suLista->toString();
    }
};
class Hospitalizacion : public Departamento {
public:
    Hospitalizacion() : Departamento("Hospitalizacion") {}
    
    void mostrarEstado() {
        cout << "--- Estado Hospitalizacion ---"<<endl;
        cout << "Pacientes en Hospitalizacion: " << this->suLista->getSize() << endl;
        cout << this->suLista->toString();
    }
};
template <typename T>
class Pila {
private:
    Nodo<T>* tope;
public:
    Pila() {
        this->tope = nullptr;
    }
    void añadir(T dato) {
        Nodo<T>* nuevo = new Nodo<T>(dato);
        nuevo->setSiguiente(this->tope);
        this->tope = nuevo;
    }
    void mostrar() {
        if (this->tope == nullptr) {
            cout << "El historial esta vacio." << endl;
            return;
        }
        Nodo<T>* aux = this->tope;
        while (aux != nullptr) {
            cout << aux->getDato() << endl;
            cout << "--" << endl;
            aux = aux->getSiguiente();
        }
    }
};

void ingresasDepartamentos(Lista<Departamento*>& hospital){
    hospital.añadir(new Urgencias());
    hospital.añadir(new MedicinaGen());
    hospital.añadir(new Cardiologia());
    hospital.añadir(new Neurología());
    hospital.añadir(new Traumatologia());
    hospital.añadir(new Cirugia());
    hospital.añadir(new Pediatria());
    hospital.añadir(new Hospitalizacion());
    
}
void verEstado(string op, Lista<Departamento*>& hospital){
    try{
        int opcion = stoi(op) - 1;
        Departamento* servicio= hospital.getIndice(opcion);
        if(servicio==nullptr){
            cout<<"No se ha encontrado el servicio"<<endl;
            return;
        }
        servicio->mostrarEstado();
        
        
    }catch(const invalid_argument& e){
        cout<<"Error!! devolviendo al menú..."<<endl;
    }
}
void parsearLinea(const string& linea, int& id, string& nombre, int& edad, string& depa) {
    const char* ptr = linea.c_str();
    string acumulador = "";
    int campo = 0;

    while (*ptr != '\0') {
        if (*ptr == ';') { 
            if (campo == 0) id = stoi(acumulador);
            else if (campo == 1) nombre = acumulador;
            else if (campo == 2) edad = stoi(acumulador);
            
            acumulador = ""; 
            campo++;
        } else if (*ptr != '\r' && *ptr != '\n') {
            acumulador += *ptr;
        }
        
        ptr++; 
    }

    if (campo == 3) {
        depa = acumulador;
    }
}
void leerArch(Lista<Paciente*>& pacientesDispo) {
    try {
        ifstream archivo("archivo.txt");
        string linea;
        
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            int id = 0, edad = 0;
            string nombre = "", departamento = "";
    
            parsearLinea(linea, id, nombre, edad, departamento);
            
            pacientesDispo.añadir(new Paciente(nombre, edad, id, departamento));
        }
        archivo.close();
        
    } catch (const exception& e) {
        cout << "Error al leer el archivo." << endl;
    }
}

int abrirMenu() {
    Lista<Departamento*> hospital;
    Lista<Paciente*> pacientesDispo;
    ingresasDepartamentos(hospital);
    Pila<string> historial;
  
    leerArch(pacientesDispo);
    int opcion;
    do {
        cout << R"(=== Hospital marmaja ===
        1. Atender pacientes
        2. Ver departamento
        3. Revisar historial de atencion
        4. Salir )" << endl;
        cout << "Opcion >";
        cin >> opcion;
        cout << "\n" << endl;
    
        switch (opcion) {
            case 1:{
                cout<<"==Pacientes en espera=="<<endl;
                if (pacientesDispo.getSize() == 0) {
                    cout << "No hay pacientes en espera." << endl << endl;
                    break;
                }
                for (int i = 0; i < pacientesDispo.getSize(); i++) {
                    Paciente* p = pacientesDispo.getIndice(i);
                    cout << (i + 1) << ". ";
                    if (p->getId() < 10) cout << "00";
                    else if (p->getId() < 100) cout << "0";
                    cout << p->getId() << "- " << p->getNombre() << endl;
                }
                
                cout << "Indique la cantidad de pacientes a atender (ingrese -1 para volver al menú): ";
                string cantStr;
                cin >> cantStr;
                int cantidad;
                try {
                    cantidad = stoi(cantStr);
                    if(cantidad==-1){
                        cout<<"Volviendo al menú"<< endl;
                        break;
                    }
                } catch (...) {
                    cout << "Cantidad invalida." << endl << endl;
                    break;
                }
                
                if (cantidad > pacientesDispo.getSize()) {
                    cantidad = pacientesDispo.getSize();
                    cout<<"Se atenderán a todos los pacientes"<<endl<<endl;
                }
                cout << "=== ATENDIENDO PACIENTES ===" << endl;
                for (int i = 0; i < cantidad; i++) {
                    Paciente* p = pacientesDispo.extraerPrimero();
                    if (p != nullptr) {
                        cout << "ID: "<< p->getId() << endl;
                        cout << "Nombre: " << p->getNombre() << endl;
                        cout << "Edad: " << p->getEdad() << endl;
                        cout << "Servicio: " << p->getDepartamento() << endl;
                        bool derivado = false;
                        for (int j = 0; j < hospital.getSize(); j++) {
                            Departamento* dep = hospital.getIndice(j);
                            if (p->getDepartamento().find(dep->getNombre()) != string::npos) {
                                dep->agregarPaciente(p);
                                string registro = "Nombre: " + p->getNombre() + "- Edad: " + to_string(p->getEdad()) + "- Departamento: " + dep->getNombre();
                                historial.añadir(registro);
                                cout << "Paciente enviado a " << p->getDepartamento() << endl<<endl;
                                derivado = true;
                                break;
                            }
                        }
                        if (!derivado) {
                            cout << "Departamento no encontrado. Paciente descartado." << endl << endl;
                            delete p;
                        }
                    }
                }
                break;}
            case 2: {
                cout<<"-- depas/sevicios--"<<endl;
                string op;
                for(int i = 0; i < hospital.getSize(); i++){
                    cout << (i+1) << ". " << hospital.getIndice(i)->getNombre() << endl;
                }
                cout<<"Seleccionar opcion: ";
                cin>> op;
                cout<<op<<endl;
                verEstado(op,hospital);
                break;}
            case 3: 
                cout << "=== HISTORIAL DE ULTIMAS ATENCIONES DEL HOSPITAL ===" << endl;
                historial.mostrar();
                cout << endl;
                break;
            case 4: 
                break;
            default:
                cout << "Error!! intente nuevamente" << endl;
        }
    } while (opcion != 4);
    cout<<"Chao"<<endl;
    return 0;
}


int main() {
   
    abrirMenu();
    return 0;
}
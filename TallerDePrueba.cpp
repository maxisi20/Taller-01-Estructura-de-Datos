#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "Paciente.cpp"
#include "Estructuras.hpp"
#include "Departamento.cpp"
using namespace std;

template <typename T>
class Pila {
private:
    Nodo<T>* tope;
public:
    Pila() {
        this->tope = nullptr;
    }
    ~Pila() {
        Nodo<T>* actual = this->tope;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->getSiguiente();
            delete actual;
            actual = siguiente;
        }
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
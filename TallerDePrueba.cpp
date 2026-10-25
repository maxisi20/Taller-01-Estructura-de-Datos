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
    hospital.anadir(new Urgencias());
    hospital.anadir(new MedicinaGen());
    hospital.anadir(new Cardiologia());
    hospital.anadir(new Neurología());
    hospital.anadir(new Traumatologia());
    hospital.anadir(new Cirugia());
    hospital.anadir(new Pediatria());
    hospital.anadir(new Hospitalizacion());
}

void verEstado(string op, Lista<Departamento*>& hospital){
    try{
        int opcion = stoi(op) - 1;
        Departamento* servicio = hospital.getIndice(opcion);
        if(servicio == nullptr){
            cout << "No se ha encontrado el servicio" << endl;
            return;
        }
        servicio->mostrarEstado();
    }catch(const invalid_argument& e){
        cout << "Error!! devolviendo al menú..." << endl;
    }
}

void parsearLinea(const string& linea, int& id, string& nombre, int& edad, double& temperatura, int& presionArterial, int& dolor, string& tipoDolor, int& trauma, int& sintomasNeurologicos, int& requiereCirugia, int& diasHospitalizacion) {
    const char* ptr = linea.c_str();
    string acumulador = "";
    int campo = 0;

    while (*ptr != '\0') {
        if (*ptr == ';') { 
            if (campo == 0) id = stoi(acumulador);
            else if (campo == 1) nombre = acumulador;
            else if (campo == 2) edad = stoi(acumulador);
            else if (campo == 3) temperatura = stod(acumulador);
            else if (campo == 4) presionArterial = stoi(acumulador);
            else if (campo == 5) dolor = stoi(acumulador);
            else if (campo == 6) tipoDolor = acumulador;
            else if (campo == 7) trauma = stoi(acumulador);
            else if (campo == 8) sintomasNeurologicos = stoi(acumulador);
            else if (campo == 9) requiereCirugia = stoi(acumulador);
            
            acumulador = ""; 
            campo++;
        } else if (*ptr != '\r' && *ptr != '\n') {
            acumulador += *ptr;
        }
        ptr++; 
    }

    if (campo == 10) {
        diasHospitalizacion = stoi(acumulador);
    }
}

void leerArch(Cola<Paciente*>& colaPacientes) {
    try {
        ifstream archivo("archivo.txt");
        string linea;
        
        while (getline(archivo, linea)) {
            if (linea.empty()) continue;

            int id = 0, edad = 0,
            presionArterial = 0, 
            dolor = 0, 
            trauma = 0, 
            sintomasNeurologicos = 0, 
            requiereCirugia = 0, 
            diasHospitalizacion = 0;
            double temperatura = 0.0;
            string nombre = "", tipoDolor = "";
    
            parsearLinea(linea, id, nombre, edad, temperatura, presionArterial, dolor, tipoDolor, trauma, sintomasNeurologicos, requiereCirugia, diasHospitalizacion);
            
            colaPacientes.encolar(new Paciente(id, nombre, edad, temperatura, presionArterial, dolor, tipoDolor, trauma, sintomasNeurologicos, requiereCirugia, diasHospitalizacion));
        }
        archivo.close();
        
    } catch (const exception& e) {
        cout << "Error al leer el archivo." << endl;
    }
}

int abrirMenu() {
    Lista<Departamento*> hospital;
    Cola<Paciente*> colaPacientes; 
    ingresasDepartamentos(hospital);
    Pila<string> historial;
  
    leerArch(colaPacientes);
    int opcion;
    do {
        cout << R"(=== HOSPITAL MARMAJA ===
1. Atender pacientes
2. Ver departamentos
3. Buscar paciente
4. Salir)" << endl;
        cout << "Seleccionar opcion: ";
        cin >> opcion;
        cout << "\n";
    
        switch (opcion) {
            case 1:{
                cout << "==Pacientes en espera (Cola)==" << endl;
                if (colaPacientes.estaVacia()) {
                    cout << "No hay pacientes en espera." << endl << endl;
                    break;
                }
                
                cout << "Indique la cantidad de pacientes a atender (ingrese -1 para volver al menú): ";
                string cantStr;
                cin >> cantStr;
                int cantidad;
                try {
                    cantidad = stoi(cantStr);
                    if(cantidad == -1){
                        cout << "Volviendo al menú" << endl;
                        break;
                    }
                } catch (...) {
                    cout << "Cantidad invalida." << endl << endl;
                    break;
                }
                
                ArbolDecision arbolDecision;

                cout << "=== ATENDIENDO PACIENTES ===" << endl;
                int atendidos = 0;
                while (atendidos < cantidad && !colaPacientes.estaVacia()) {
                    Paciente* p = colaPacientes.desencolar(); 
                    if (p != nullptr) {
                        cout << "ID: ";
                        if (p->getId() < 10) cout << "00";
                        else if (p->getId() < 100) cout << "0";
                        cout << p->getId() << endl;

                        cout << "Nombre: " << p->getNombre() << endl;
                        cout << "Edad: " << p->getEdad() << endl;
                        cout << "Temperatura: " << p->getTemperatura() << endl;
                        cout << "Dolor: " << p->getDolor() << endl;
                        cout << "TipoDolor: " << p->getTipoDolor() << endl;
                        cout << "Trauma: " << p->getTrauma() << endl;
                        cout << "SintomasNeurologicos: " << p->getSintomasNeurologicos() << endl;
                        cout << "RequiereCirugia: " << p->getRequiereCirugia() << endl;
                        cout << "DiasHospitalizacion: " << p->getDiasHospitalizacion() << endl;
                        
                        string rutaDecision = "";
                        string servicioDestino = arbolDecision.clasificar(p, rutaDecision);
                        
                        if (servicioDestino.empty()) {
                            cout << "Paciente rechazado por validacion: " << rutaDecision << endl << endl;
                            delete p;
                            atendidos++;
                            continue;
                        }
                        
                        p->setDepartamento(servicioDestino);
                        cout << "Ruta: " << rutaDecision << endl;
                        cout << "Servicio asignado: " << p->getDepartamento() << endl;
                        
                        bool derivado = false;
                        for (int j = 0; j < hospital.getSize(); j++) {
                            Departamento* dep = hospital.getIndice(j);
                            if (p->getDepartamento().find(dep->getNombre()) != string::npos) {
                                dep->agregarPaciente(p); 
                                string registro = "Nombre: " + p->getNombre() + "- Edad: " + to_string(p->getEdad()) + "- Departamento: " + dep->getNombre();
                                historial.añadir(registro);
                                cout << "Paciente insertado en el AVL de " << dep->getNombre() << "." << endl << endl;
                                derivado = true;
                                break;
                            }
                        }
                        if (!derivado) {
                            cout << "Departamento no encontrado. Paciente descartado." << endl << endl;
                            delete p;
                        }
                        atendidos++;
                    }
                }
                break;
            }
            case 2: {
                cout << "=== ESTADO DE LOS DEPARTAMENTOS ===" << endl;
                for(int i = 0; i < hospital.getSize(); i++){
                    Departamento* dep = hospital.getIndice(i);
                    cout << dep->getNombre() << endl;
                    dep->mostrarEstado();
                }
                cout << endl;
                break;
            }
            case 3: {
                cout << "=== BUSCAR PACIENTE ===" << endl;
                cout << "Indique el ID o Nombre del paciente: ";
                string busqueda;
                cin >> busqueda;
                cout << "Buscando en AVL..." << endl;

                Paciente* encontrado = nullptr;
                string depEncontrado = "";

                for (int i = 0; i < hospital.getSize(); i++) {
                    Departamento* dep = hospital.getIndice(i);
                    try {
                        int idBuscado = stoi(busqueda);
                        encontrado = dep->buscarPacientePorId(idBuscado);
                    } catch (...) {
                        encontrado = dep->buscarPacientePorNombre(busqueda);
                    }
                    if (encontrado != nullptr) {
                        depEncontrado = dep->getNombre();
                        break;
                    }
                }

                if (encontrado != nullptr) {
                    cout << "Paciente encontrado:" << endl;
                    cout << "-------" << endl;
                    cout << "ID: ";
                    if (encontrado->getId() < 10) cout << "00";
                    else if (encontrado->getId() < 100) cout << "0";
                    cout << encontrado->getId() << endl;
                    cout << "Nombre: " << encontrado->getNombre() << endl;
                    cout << "Edad: " << encontrado->getEdad() << endl;
                    cout << "Departamento: " << depEncontrado << endl;
                    cout << "T: " << encontrado->getTemperatura() << "° | D: " << encontrado->getDolor() 
                         << " | TD: " << encontrado->getTipoDolor() 
                         << " | T: " << (encontrado->getTrauma() == 1 ? "Si" : "No") 
                         << " | SN: " << (encontrado->getSintomasNeurologicos() == 1 ? "Si" : "No") 
                         << " | RC: " << (encontrado->getRequiereCirugia() == 1 ? "Si" : "No") 
                         << " | DH: " << (encontrado->getDiasHospitalizacion() > 0 ? to_string(encontrado->getDiasHospitalizacion()) : "Ninguno") << endl;
                    cout << "-------" << endl << endl;
                } else {
                    cout << "Paciente no encontrado." << endl << endl;
                }
                break;
            }
            case 4: 
                break;
            default:
                cout << "Error!! intente nuevamente" << endl;
        }
    } while (opcion != 4);
    cout << "Chao" << endl;
    return 0;
}

int main() {
    abrirMenu();
    return 0;
}
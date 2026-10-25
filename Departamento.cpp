#include "Departamento.hpp"

Departamento::Departamento(string nombre) {
    this->nombre = nombre;
    this->arbolPacientes = new ArbolAVL<Paciente*>();
}
Departamento::~Departamento() {
    delete this->arbolPacientes;
}
void Departamento::agregarPaciente(Paciente* paciente) {
    this->arbolPacientes->insertar(paciente);
}

string Departamento::getNombre() {
    return nombre;
}

string Departamento::toString() {
    return this->nombre + "\n";
}

Urgencias::Urgencias() : Departamento("Urgencias") {}
void Urgencias::mostrarEstado() {
    cout << "--- Estado Urgencias ---" << endl;
    cout << "Pacientes en urgencias: " << this->arbolPacientes->getSize() << endl;
    this->arbolPacientes->mostrarInOrden();
}

MedicinaGen::MedicinaGen() : Departamento("Medicina General") {}
void MedicinaGen::mostrarEstado() {
    cout << "--- Estado Medicina General ---" << endl;
    cout << "Pacientes en Medicina General: " << this->arbolPacientes->getSize() << endl;
    this->arbolPacientes->mostrarInOrden();
}

Cardiologia::Cardiologia() : Departamento("Cardiologia") {}
void Cardiologia::mostrarEstado() {
    cout << "--- Estado Cardiologia ---" << endl;
    cout << "Pacientes en Cardiologia: " << this->arbolPacientes->getSize() << endl;
    this->arbolPacientes->mostrarInOrden();
}

Neurología::Neurología() : Departamento("Neurología") {}
void Neurología::mostrarEstado() {
    cout << "--- Estado Neurología ---" << endl;
    cout << "Pacientes en Neurología: " << this->arbolPacientes->getSize() << endl;
    this->arbolPacientes->mostrarInOrden();
}

Traumatologia::Traumatologia() : Departamento("Traumatologia") {}
void Traumatologia::mostrarEstado() {
    cout << "--- Estado Traumatologia ---" << endl;
    cout << "Pacientes en Traumatologia: " << this->arbolPacientes->getSize() << endl;
    this->arbolPacientes->mostrarInOrden();
}

Cirugia::Cirugia() : Departamento("Cirugia") {}
void Cirugia::mostrarEstado() {
    cout << "--- Estado Cirugia ---" << endl;
    cout << "Pacientes en Cirugia: " << this->arbolPacientes->getSize() << endl;
    this->arbolPacientes->mostrarInOrden();
}

Pediatria::Pediatria() : Departamento("Pediatria") {}
void Pediatria::mostrarEstado() {
    cout << "--- Estado Pediatria ---" << endl;
    cout << "Pacientes en Pediatria: " << this->arbolPacientes->getSize() << endl;
    this->arbolPacientes->mostrarInOrden();
}

Hospitalizacion::Hospitalizacion() : Departamento("Hospitalizacion") {}
void Hospitalizacion::mostrarEstado() {
    cout << "--- Estado Hospitalizacion ---" << endl;
    cout << "Pacientes en Hospitalizacion: " << this->arbolPacientes->getSize() << endl;
    this->arbolPacientes->mostrarInOrden();
}
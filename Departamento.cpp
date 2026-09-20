#include "Departamento.hpp"

Departamento::Departamento(string nombre) {
    this->nombre = nombre;
    this->suLista = new Lista<Paciente*>();
}
Departamento::~Departamento() {
    delete this->suLista;
}
void Departamento::agregarPaciente(Paciente* paciente) {
    suLista->añadir(paciente);
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
    cout << "Pacientes en urgencias: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
}

MedicinaGen::MedicinaGen() : Departamento("Medicina General") {}
void MedicinaGen::mostrarEstado() {
    cout << "--- Estado Medicina General ---" << endl;
    cout << "Pacientes en Medicina General: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
}

Cardiologia::Cardiologia() : Departamento("Cardiologia") {}
void Cardiologia::mostrarEstado() {
    cout << "--- Estado Cardiologia ---" << endl;
    cout << "Pacientes en Cardiologia: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
}

Neurología::Neurología() : Departamento("Neurología") {}
void Neurología::mostrarEstado() {
    cout << "--- Estado Neurología ---" << endl;
    cout << "Pacientes en Neurología: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
}

Traumatologia::Traumatologia() : Departamento("Traumatologia") {}
void Traumatologia::mostrarEstado() {
    cout << "--- Estado Traumatologia ---" << endl;
    cout << "Pacientes en Traumatologia: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
}

Cirugia::Cirugia() : Departamento("Cirugia") {}
void Cirugia::mostrarEstado() {
    cout << "--- Estado Cirugia ---" << endl;
    cout << "Pacientes en Cirugia: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
}

Pediatria::Pediatria() : Departamento("Pediatria") {}
void Pediatria::mostrarEstado() {
    cout << "--- Estado Pediatria ---" << endl;
    cout << "Pacientes en Pediatria: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
}

Hospitalizacion::Hospitalizacion() : Departamento("Hospitalizacion") {}
void Hospitalizacion::mostrarEstado() {
    cout << "--- Estado Hospitalizacion ---" << endl;
    cout << "Pacientes en Hospitalizacion: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
}
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

Paciente* Departamento::buscarPacientePorId(int id) {
    return this->arbolPacientes->buscar(id);
}

Paciente* Departamento::buscarPacientePorNombre(string nombre) {
    return this->arbolPacientes->buscarPorNombre(nombre);
}

Urgencias::Urgencias() : Departamento("Urgencias") {}
void Urgencias::mostrarEstado() {
<<<<<<< Updated upstream
    cout << "--- Estado Urgencias ---" << endl;
    cout << "Pacientes en urgencias: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
=======
    if (this->arbolPacientes->getSize() == 0) {
        cout << "Sin pacientes" << endl;
    } else {
        this->arbolPacientes->mostrarInOrden();
    }
>>>>>>> Stashed changes
}

MedicinaGen::MedicinaGen() : Departamento("Medicina General") {}
void MedicinaGen::mostrarEstado() {
<<<<<<< Updated upstream
    cout << "--- Estado Medicina General ---" << endl;
    cout << "Pacientes en Medicina General: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
=======
    if (this->arbolPacientes->getSize() == 0) {
        cout << "Sin pacientes" << endl;
    } else {
        this->arbolPacientes->mostrarInOrden();
    }
>>>>>>> Stashed changes
}

Cardiologia::Cardiologia() : Departamento("Cardiologia") {}
void Cardiologia::mostrarEstado() {
<<<<<<< Updated upstream
    cout << "--- Estado Cardiologia ---" << endl;
    cout << "Pacientes en Cardiologia: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
=======
    if (this->arbolPacientes->getSize() == 0) {
        cout << "Sin pacientes" << endl;
    } else {
        this->arbolPacientes->mostrarInOrden();
    }
>>>>>>> Stashed changes
}

Neurología::Neurología() : Departamento("Neurología") {}
void Neurología::mostrarEstado() {
<<<<<<< Updated upstream
    cout << "--- Estado Neurología ---" << endl;
    cout << "Pacientes en Neurología: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
=======
    if (this->arbolPacientes->getSize() == 0) {
        cout << "Sin pacientes" << endl;
    } else {
        this->arbolPacientes->mostrarInOrden();
    }
>>>>>>> Stashed changes
}

Traumatologia::Traumatologia() : Departamento("Traumatologia") {}
void Traumatologia::mostrarEstado() {
<<<<<<< Updated upstream
    cout << "--- Estado Traumatologia ---" << endl;
    cout << "Pacientes en Traumatologia: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
=======
    if (this->arbolPacientes->getSize() == 0) {
        cout << "Sin pacientes" << endl;
    } else {
        this->arbolPacientes->mostrarInOrden();
    }
>>>>>>> Stashed changes
}

Cirugia::Cirugia() : Departamento("Cirugia") {}
void Cirugia::mostrarEstado() {
<<<<<<< Updated upstream
    cout << "--- Estado Cirugia ---" << endl;
    cout << "Pacientes en Cirugia: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
=======
    if (this->arbolPacientes->getSize() == 0) {
        cout << "Sin pacientes" << endl;
    } else {
        this->arbolPacientes->mostrarInOrden();
    }
>>>>>>> Stashed changes
}

Pediatria::Pediatria() : Departamento("Pediatria") {}
void Pediatria::mostrarEstado() {
<<<<<<< Updated upstream
    cout << "--- Estado Pediatria ---" << endl;
    cout << "Pacientes en Pediatria: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
=======
    if (this->arbolPacientes->getSize() == 0) {
        cout << "Sin pacientes" << endl;
    } else {
        this->arbolPacientes->mostrarInOrden();
    }
>>>>>>> Stashed changes
}

Hospitalizacion::Hospitalizacion() : Departamento("Hospitalizacion") {}
void Hospitalizacion::mostrarEstado() {
<<<<<<< Updated upstream
    cout << "--- Estado Hospitalizacion ---" << endl;
    cout << "Pacientes en Hospitalizacion: " << this->suLista->getSize() << endl;
    cout << this->suLista->toString();
=======
    if (this->arbolPacientes->getSize() == 0) {
        cout << "Sin pacientes" << endl;
    } else {
        this->arbolPacientes->mostrarInOrden();
    }
>>>>>>> Stashed changes
}
#include <iostream>
#include "Paciente.hpp"

using namespace std;

Paciente::Paciente() {}

Paciente::Paciente(string nombre, int edad, int id, string departamento) {
    this->nombre = nombre;
    this->edad = edad;
    this->id = id;
    this->departamento = departamento;
}

Paciente::~Paciente() {
        cout << "Ya fue atendido " << nombre << endl;
}

string Paciente::getNombre() {
    return this->nombre;
}

int Paciente::getEdad() {
    return this->edad;
}

string Paciente::toString() {
    return this->nombre + " (" + to_string(edad) + ")\n";
}

int Paciente::getId() {
    return this->id;
}

string Paciente::getDepartamento() {
    return this->departamento;
}
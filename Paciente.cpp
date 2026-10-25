#include <iostream>
#include "Paciente.hpp"

using namespace std;

Paciente::Paciente() {}

Paciente::Paciente(int id, string nombre, int edad, double temperatura, int presionArterial, int dolor, string tipoDolor, int trauma, int sintomasNeurologicos, int requiereCirugia, int diasHospitalizacion) {
    this->id = id;
    this->nombre = nombre;
    this->edad = edad;
    this->temperatura = temperatura;
    this->presionArterial = presionArterial;
    this->dolor = dolor;
    this->tipoDolor = tipoDolor;
    this->trauma = trauma;
    this->sintomasNeurologicos = sintomasNeurologicos;
    this->requiereCirugia = requiereCirugia;
    this->diasHospitalizacion = diasHospitalizacion;
    this->departamento = "";
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

int Paciente::getId() {
    return this->id;
}

double Paciente::getTemperatura() {
    return this->temperatura;
}

int Paciente::getPresionArterial() {
    return this->presionArterial;
}

int Paciente::getDolor() {
    return this->dolor;
}

string Paciente::getTipoDolor() {
    return this->tipoDolor;
}

int Paciente::getTrauma() {
    return this->trauma;
}

int Paciente::getSintomasNeurologicos() {
    return this->sintomasNeurologicos;
}

int Paciente::getRequiereCirugia() {
    return this->requiereCirugia;
}

int Paciente::getDiasHospitalizacion() {
    return this->diasHospitalizacion;
}

string Paciente::getDepartamento() {
    return this->departamento;
}

void Paciente::setDepartamento(string departamento) {
    this->departamento = departamento;
}

string Paciente::toString() {
    return this->nombre + " (" + to_string(edad) + ")\n";
}
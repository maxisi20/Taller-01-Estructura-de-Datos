#pragma once
#include <string>

class Paciente {
private:
    int id;
    std::string nombre;
    int edad;
    std::string departamento;

public:
    Paciente();
    Paciente(std::string nombre, int edad, int id, std::string departamento);
    ~Paciente();

    std::string getNombre();
    int getEdad();
    int getId();
    std::string getDepartamento();
    std::string toString();
};
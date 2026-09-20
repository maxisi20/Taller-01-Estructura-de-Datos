#ifndef DEPARTAMENTO_HPP
#define DEPARTAMENTO_HPP

#include <iostream>
#include <string>
#include "Estructuras.hpp"
#include "Paciente.hpp"

using namespace std;

class Departamento {

protected:
    Lista<Paciente*>* suLista;
    string nombre;

public:
    Departamento(string nombre);
    virtual ~Departamento();   

    void agregarPaciente(Paciente* paciente);
    string getNombre();
    string toString();

    virtual void mostrarEstado() = 0;
};

class Urgencias : public Departamento {
public:
    Urgencias();
    void mostrarEstado() override;
};

class MedicinaGen : public Departamento {
public:
    MedicinaGen();
    void mostrarEstado() override;
};

class Cardiologia : public Departamento {
public:
    Cardiologia();
    void mostrarEstado() override;
};

class Neurología : public Departamento {
public:
    Neurología();
    void mostrarEstado() override;
};

class Traumatologia : public Departamento {
public:
    Traumatologia();
    void mostrarEstado() override;
};

class Cirugia : public Departamento {
public:
    Cirugia();
    void mostrarEstado() override;
};

class Pediatria : public Departamento {
public:
    Pediatria();
    void mostrarEstado() override;
};

class Hospitalizacion : public Departamento {
public:
    Hospitalizacion();
    void mostrarEstado() override;
};

#endif
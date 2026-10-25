#pragma once
#include <string>

class Paciente {
private:
    int id;
    std::string nombre;
    int edad;
    double temperatura;
    int presionArterial;
    int dolor;                
    std::string tipoDolor;     
    int trauma;                
    int sintomasNeurologicos;  
    int requiereCirugia;       
    int diasHospitalizacion;    
    std::string departamento;   

public:
    Paciente();
    Paciente(int id, std::string nombre, int edad, double temperatura, int presionArterial, 
             int dolor, std::string tipoDolor, int trauma, int sintomasNeurologicos, 
             int requiereCirugia, int diasHospitalizacion);
    ~Paciente();

    // Getters
    int getId();
    std::string getNombre();
    int getEdad();
    double getTemperatura();
    int getPresionArterial();
    int getDolor();
    std::string getTipoDolor();
    int getTrauma();
    int getSintomasNeurologicos();
    int getRequiereCirugia();
    int getDiasHospitalizacion();
    std::string getDepartamento();

   // Setters
    void setDepartamento(std::string dep);

    std::string toString();
};
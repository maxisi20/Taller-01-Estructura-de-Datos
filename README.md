# Taller 01: Sistema de Gestión Hospitalaria

Este proyecto corresponde al primer taller de la asignatura Estructuras de Datos. Desarrollamos un programa modular en C++ para administrar el flujo de pacientes y la atención por departamentos dentro de un hospital.

---

## Integrantes

*  Maximiliano Yañez
* 21.668.966-6
* maxisi20
* ITI

* **Nombre:** [Nombre integrante 2]
  * **RUT:** [RUT]
  * **GitHub:** [Usuario de GitHub]
  * **Carrera:** [Carrera]

---

## Estructuras de Datos (Implementación Manual)

Tal como solicita la pauta del taller, no utilizamos la librería estándar STL (`std::list`, `std::stack`, `std::vector`, etc.). Todas las estructuras fueron programadas de forma manual utilizando plantillas (*templates*):

* **Nodo (`Nodo<T>`):** Estructura elemental para almacenar el dato y el puntero al siguiente elemento.
* **Lista Enlazada (`Lista<T>`):** Maneja la lista de pacientes en cada departamento y la lista general de departamentos.
* **Pila (`Pila<T>`):** Implementación de tipo LIFO para gestionar historiales o registros de atenciones.

---

## Estructura de Archivos

* `Estructuras.hpp`: Implementación completa de las clases dinámicas `Nodo`, `Lista` y `Pila`.
* `Paciente.hpp` / `Paciente.cpp`: Definición y lógica asociada a los pacientes.
* `Departamento.hpp` / `Departamento.cpp`: Clase base `Departamento` y sus clases derivadas (Urgencias, Cardiología, Neurología, etc.).
* `TallerDePrueba.cpp`: Archivo principal con la función `main` y las pruebas del sistema.

---

## Compilación y Ejecución

Al ser un proyecto modularizado con múltiples archivos de origen, la compilación requiere enlazar todos los archivos `.cpp` simultáneamente.

### En Windows (PowerShell / Terminal)

1. Abrir la terminal en la carpeta del proyecto.
2. Compilar ejecutando:
   ```powershell
   g++ TallerDePrueba.cpp Paciente.cpp Departamento.cpp -o programa.exe
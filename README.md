# Taller 01: Sistema de Gestión Hospitalaria

Este proyecto corresponde al primer taller de la asignatura Estructuras de Datos. Desarrollamos un programa modular en C++ para administrar el flujo de pacientes y la atención por departamentos dentro de un hospital.

---

## Integrantes

*  Maximiliano Yañez
  * 21.668.966-6
  * maxisi20
  * ITI

* José Urtubia
  * 22.017.611-8
  * Jose-Urtubia
  * ICCI

---

## Estructuras de Datos (Implementación Manual)

Tal como solicita la pauta del taller, no utilizamos la librería estándar STL (`std::list`, `std::stack`, `std::vector`, etc.). Todas las estructuras fueron programadas de forma manual utilizando plantillas (*templates*):

* **Nodo (`Nodo<T>`):** Estructura elemental para almacenar el dato y el puntero al siguiente elemento.
* **Lista Enlazada (`Lista<T>`):** Maneja la lista de pacientes en cada departamento y la lista general de departamentos.
* **Pila (`Pila<T>`):** Implementación de tipo LIFO para gestionar historiales o registros de atenciones.
** Arbol AVL (`ArbolAVL<T>`)	:** Un AVL por servicio, con el ID como clave. Rotaciones simples (izquierda y derecha) y dobles (izquierda-derecha y derecha-izquierda).
**Arbol de decisiones (`ArbolDecision`):**	Árbol binario de nodos y punteros que determina el servicio.
---

## Estructura de Archivos

* `Estructuras.hpp`: Implementación completa de las clases dinámicas `Nodo`, `Lista`,`Pila`, `Cola`, `NodoDecision` y `ArbolDecision`
* `Paciente.hpp` / `Paciente.cpp`: Definición y lógica asociada a los pacientes.
* `Departamento.hpp` / `Departamento.cpp`: Clase base `Departamento` y sus clases derivadas (Urgencias, Cardiología, Neurología, etc. Cada uno con su AVL).
* `TallerDePrueba.cpp`: Archivo principal con la función `main` y las pruebas del sistema.

---
## Árbol de decisión
* El árbol se construyó respondiendo, en este orden, a las preguntas que haría un triage hospitalario. Cada pregunta separa un grupo de pacientes que ya tiene un servicio claro:

* ¿Es un niño? Los menores van a un servicio especializado sin importar la dolencia.
* ¿Es una emergencia? Si hay signos de gravedad, se estabiliza primero en Urgencias.
* ¿Hay una lesión? Si hay trauma, se decide entre Cirugía y Traumatología.
* ¿Hay una especialidad clara? Neurología, Cirugía (sin trauma) y Cardiología.
* ¿Es un paciente estable? Se decide entre Hospitalización y Medicina General.
Los umbrales usan `>=`, de modo que el valor exacto del umbral sí cumple la condición.

### Tabla de decisiones (en el orden de evaluación)

*Prioridad:* se evalúa de arriba hacia abajo y gana la **primera** condición que se cumple.

| Nivel | Condición evaluada | Si se cumple | Si no se cumple | Justificación |
|:---:|:---|:---:|:---:|:---|
| **1** | `Edad < 14` | **Pediatría** | Pasa al nivel 2 | Los menores de 14 años se atienden en Pediatría. |
| **2** | `Dolor >= 8` | **Urgencias** | Pasa al nivel 3 | Dolor intenso (escala 0-10) se considera emergencia. |
| **3** | `Temperatura >= 39.5` | **Urgencias** | Pasa al nivel 4 | Fiebre alta se considera emergencia. |
| **4** | `Trauma == 1` | Pasa al nivel 4a | Pasa al nivel 5 | Una lesión requiere evaluar si es quirúrgica. |
| **4a** | `RequiereCirugia == 1` | **Cirugía** | **Traumatología** | Con trauma: si requiere operación va a Cirugía; si no, a Traumatología. |
| **5** | `SintomasNeurologicos == 1` | **Neurología** | Pasa al nivel 6 | Síntomas neurológicos corresponden a Neurología. |
| **6** | `RequiereCirugia == 1` | **Cirugía** | Pasa al nivel 7 | Un paciente quirúrgico sin trauma (ej. dolor abdominal) también va a Cirugía. |
| **7** | `TipoDolor == pecho` | **Cardiología** | Pasa al nivel 8 | El dolor de pecho es una señal cardíaca. |
| **8** | `PresionArterial >= 180` | **Cardiología** | Pasa al nivel 9 | Presión sistólica de 180 mmHg o más es crisis hipertensiva. |
| **9** | `DiasHospitalizacion >= 2` | **Hospitalización** | **Medicina General** | Una estadía de 2 días o más requiere internación; si no, atención general. |



*Empates y prioridades*
* Si un paciente cumple varias condiciones, gana la primera que se cumple de arriba hacia abajo. El orden de la tabla es la prioridad.
* Ejemplo: un paciente con dolor de pecho y dolor 9 va a Urgencias (nivel 2), no a Cardiología (nivel 7), porque la emergencia se estabiliza primero.
* Ejemplo: un menor de 14 años con fiebre alta va a Pediatría (nivel 1).


## Compilación y Ejecución

Al ser un proyecto modularizado con múltiples archivos de origen, la compilación requiere enlazar todos los archivos `.cpp` simultáneamente.

### En Windows (PowerShell / Terminal)

1. Abrir la terminal en la carpeta del proyecto.
2. Compilar ejecutando:
   ```powershell
   g++ TallerDePrueba.cpp Paciente.cpp Departamento.cpp -o programa.exe

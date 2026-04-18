#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "NodoDoble.h"

class ListaDoble {
private:
    NodoDoble* cabeza;  // primera canción
    NodoDoble* cola;    // última canción 
    NodoDoble* actual;  // canción que está sonando 

public:
    // Constructor y Destructor
    ListaDoble();
    ~ListaDoble();

    // Métodos principales
    void agregarAlFinal(Cancion* c);
    void siguientePista();
    void pistaAnterior();
    
    // Aquí luego agregaremos más, como imprimir(), etc.
};

#endif
#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "NodoDoble.h"

class ListaDoble {
private:
    NodoDoble* cabeza;  //primera canción
    NodoDoble* cola;    //ultima canción 
    NodoDoble* actual;  //canción que está sonando 

public:
    //Constructor y Destructor
    ListaDoble();
    ~ListaDoble();

    //metodos principales
    void agregarAlFinal(Cancion c);
    void siguientePista();
    void pistaAnterior();

    
    //Para que el main sepa qué mostrar 
    Cancion* obtenerActual(); 
    bool tieneActual();

    void Mostrarcoladesdeactual();
    void Saltarpistas(int cantidad);
};

#endif
#include "ListaDoble.h"
#include <iostream>


ListaDoble::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
    actual = nullptr;
}


ListaDoble::~ListaDoble() {}

// Método para agregar una canción al final de la lista
void ListaDoble::agregarAlFinal(Cancion* c) {
    //  creamos el nuevo nodo en la memoria dinámica
    NodoDoble* nuevoNodo = new NodoDoble(c);

    // la lista está vacía?
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
        // si es la primera canción, la definimos como la actual por defecto
        if (actual == nullptr) {
            actual = nuevoNodo;
        }
    } 
    // si ya hay canciones, la enganchamos al final
    else {
        cola->setSiguiente(nuevoNodo); // el ultimo de ahora apunta al nuevo
        nuevoNodo->setAnterior(cola);  // el nuevo apunta hacia atrás al que era el último
        cola = nuevoNodo;            // actualizamos la etiqueta "cola" al nuevo nodo
    }
}
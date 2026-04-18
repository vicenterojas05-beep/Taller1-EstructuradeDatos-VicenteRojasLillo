#include "NodoDoble.h"

// constructor
NodoDoble::NodoDoble(Cancion* c) {
    cancion = c;
    siguiente = nullptr;
    anterior = nullptr;
    
}

// getters
Cancion* NodoDoble::getCancion() { 
    return cancion; }
NodoDoble* NodoDoble::getSiguiente() {
     return siguiente; }
NodoDoble* NodoDoble::getAnterior() { 
    return anterior; }

// setters
void NodoDoble::setSiguiente(NodoDoble* nodo) {
     siguiente = nodo; }
void NodoDoble::setAnterior(NodoDoble* nodo) { 
    anterior = nodo; }
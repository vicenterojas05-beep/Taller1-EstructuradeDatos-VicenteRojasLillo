#include "Listadoble.h"
#include <iostream>


ListaDoble::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
    actual = nullptr;
}


ListaDoble::~ListaDoble() {}

//metodo para agregar una canción al final de la lista
void ListaDoble::agregarAlFinal(Cancion c) {
    
    NodoDoble* nuevoNodo = new NodoDoble(c);

    // la lista esta vacía?
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
        // si es la primera canción, la definimos como la actual 
        if (actual == nullptr) {
            actual = nuevoNodo;
        }
    } 
    // si ya hay canciones, la enganchamos al final
    else {
        cola->setSiguiente(nuevoNodo); // el ultimo de ahora apunta al nuevo
        nuevoNodo->setAnterior(cola);  // el nuevo apunta hacia atrás al que era el último
        cola = nuevoNodo;            // actualizamos la variable cola al nuevo nodo
    }
}

void ListaDoble::siguientePista(int repeticion) {
    if (actual == nullptr) return;

    //si es R1 (1) la cancion se repite continuamente el puntero no avanza.
    if (repeticion == 1) {
        return; 
    }

    if (actual->getSiguiente() != nullptr) {
        //avance normal
        actual = actual->getSiguiente();
    } else if (repeticion == 2) {
        //repeticion de la lista, del final saltamos al principio
        actual = cabeza; 
    } else {
        cout << ">> Estas en la ultima cancion. No hay mas pistas.\n";
    }
}

// Retroceder a la pista anterior
void ListaDoble::pistaAnterior(int repeticion) {
   if (actual == nullptr) return;

    // Si es R1 (1), el puntero no retrocede.
    if (repeticion == 1) {
        return; 
    }

    if (actual->getAnterior() != nullptr) {
        // Retroceso normal
        actual = actual->getAnterior();
    } else if (repeticion == 2) {
        // Magia del RA (2): del principio saltamos al final
        actual = cola; 
    } else {
        cout << ">> Estas en la primera cancion.\n";
    }
}

//devolver la canción actual para el menu
Cancion* ListaDoble::obtenerActual() {
    if (actual != nullptr){
        return &(actual->getCancion());
    }
    return nullptr;
}

bool ListaDoble::tieneActual() {
    return actual != nullptr;
}

void ListaDoble::Mostrarcoladesdeactual() {
    if (actual == nullptr) {
        cout << ">> La lista esta vacia.\n";
        return;
    }

    //empezamos a mirar desde la canción que le sigue a la actual
    NodoDoble* temp = actual->getSiguiente(); 
    int contador = 1;

    cout << "\n--- COLA DE REPRODUCCION ---\n";
    while (temp != nullptr) {
        cout << contador << ". " << temp->getCancion().nombre << " - " << temp->getCancion().artista << " (" << temp->getCancion().duracion << " seg)\n";
        temp = temp->getSiguiente(); //avanzamos al siguiente nodo
        contador++;
    }

    if (contador == 1) {
        cout << ">> No hay mas canciones en espera.\n";
    }
    cout << "----------------------------\n";
}
void ListaDoble::Saltarpistas(int cantidad) {
    if (actual == nullptr) return; // Si no hay nada sonando, no hacemos nada

    int saltados = 0;
    
    for (int i = 0; i < cantidad; i++) {
        // Mientras exista una canción siguiente, avanzamos
        if (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
            saltados++;
        } else {
            cout << ">> Se alcanzo el final de la lista. Solo se saltaron " << saltados << " pistas.\n";
            return; // Salimos de la función prematuramente
        }
    }
    
    cout << ">> Se saltaron " << cantidad << " pistas con exito.\n";
}

void ListaDoble::Mostrarlistadocompleto() {
    NodoDoble* temp = cabeza;
    
    if (temp == nullptr) {
        cout << ">> La lista de reproduccion esta vacia.\n";
        return;
    }

    cout << "==============================================\n";
    cout << "        LISTADO COMPLETO DE CANCIONES        \n";
    cout << "==============================================\n";
    
    while (temp != nullptr) {
        cout << "[" << temp->getCancion().id << "] "  << temp->getCancion().nombre << " - " << temp->getCancion().artista << " (" << temp->getCancion().duracion << " seg)\n";
           
        temp = temp->getSiguiente();
    }
    cout << "========================================================\n";
}

void ListaDoble::Fijarporid(int Id_buscado) {
    NodoDoble* Temp = cabeza;
    
    while (Temp != nullptr) {
        if (Temp->getCancion().id == Id_buscado) {
            actual = Temp; // encontramos la cancion y la fijamos como actual
            return;
        }
        Temp = Temp->getSiguiente();
    }
}

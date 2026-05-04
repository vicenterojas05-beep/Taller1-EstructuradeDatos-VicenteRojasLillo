#include "Listadoble.h"
#include <iostream>
#include <cstdlib>

ListaDoble::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
    actual = nullptr;
}


ListaDoble::~ListaDoble() {}


void ListaDoble::siguientePista(int repeticion, bool aleatorio) {
    if (actual == nullptr) return;

    if (repeticion == 1) return; //R1 se queda en la misma

    if (actual->getSiguiente() != nullptr) {
        actual = actual->getSiguiente();
    } else if (repeticion == 2) {
        //volvemos al principio
        actual = cabeza; 
        
        //Si el aleatorio esta activo, re-mezclamos al iniciar el ciclo
        if (aleatorio) {
            Mezclarrestantes();
        }
    } else {
        cout << ">> Estas en la ultima cancion. No hay mas pistas.\n";
    }
}

// Retroceder a la pista anterior
void ListaDoble::pistaAnterior(int repeticion,bool aleatorio) {
   if (actual == nullptr) return;

    if (actual == nullptr) return;
    if (repeticion == 1) return; 

    if (actual->getAnterior() != nullptr) {
        actual = actual->getAnterior();
    } else if (repeticion == 2) {
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

int ListaDoble::Obtenerultimoid() {
    if (cabeza == nullptr) return 0; // Si no hay canciones, el ultimo ID es 0
    
    NodoDoble* Temp = cabeza;
    while (Temp->getSiguiente() != nullptr) {
        Temp = Temp->getSiguiente();
    }
    return Temp->getCancion().id; // Devolvemos el ID de la ultima pista
}

void ListaDoble::Agregaralfinal(Cancion Nueva_cancion) {
    NodoDoble* Nuevo = new NodoDoble(Nueva_cancion);
    

    if (cabeza == nullptr) {
        cabeza = Nuevo;
        cola = Nuevo; // (Mantenemos la cola actualizada por si se usa)
    } else {
        NodoDoble* Temp = cabeza;
        while (Temp->getSiguiente() != nullptr) {
            Temp = Temp->getSiguiente();
        }
        Temp->setSiguiente(Nuevo);
        Nuevo->setAnterior(Temp);
        cola = Nuevo;
    }
}
Cancion* ListaDoble::Buscarporid(int id_buscado) {
    NodoDoble* Temp = cabeza;
    while (Temp != nullptr) {
        if (Temp->getCancion().id == id_buscado) {
            return &(Temp->getCancion()); //retornamos un puntero a los datos de la cancion
        }
        Temp = Temp->getSiguiente();
    }
    return nullptr; //retorna nulo si el ID no existe
}
bool ListaDoble::Eliminarnodo(int id_borrar) {
    NodoDoble* Temp = cabeza;
    while (Temp != nullptr) {
        if (Temp->getCancion().id == id_borrar) {
            // Si es la cabeza
            if (Temp == cabeza) {
                cabeza = Temp->getSiguiente();
                if (cabeza != nullptr) cabeza->setAnterior(nullptr);
            } 
            // Si es la cola
            else if (Temp == cola) {
                cola = Temp->getAnterior();
                if (cola != nullptr) cola->setSiguiente(nullptr);
            } 
            // Si esta en medio
            else {
                Temp->getAnterior()->setSiguiente(Temp->getSiguiente());
                Temp->getSiguiente()->setAnterior(Temp->getAnterior());
            }
            
            // Si resulta que la cancion actual era la que acabamos de borrar
            if (actual == Temp) {
                actual = nullptr; // Se detiene la reproduccion
            }
            
            delete Temp; // Liberamos memoria
            return true;
        }
        Temp = Temp->getSiguiente();
    }
    return false;
}

void ListaDoble::Mezclarrestantes() {
    //si no hay cancion actual o no hay canciones siguientes, no hay nada que mezclar
    if (actual == nullptr || actual->getSiguiente() == nullptr) {
        return; 
    }

    //primero contamos manualmente cuantos nodos quedan por mezclar
    int Cantidad = 0;
    NodoDoble* Temp = actual->getSiguiente();
    while (Temp != nullptr) {
        Cantidad++;
        Temp = Temp->getSiguiente();
    }

    //Creamos un arreglo dinamico de punteros de forma manual (sin stl)
    NodoDoble** Arreglo_nodos = new NodoDoble*[Cantidad];

    //llenamos el arreglo con los punteros a los nodos
    Temp = actual->getSiguiente();
    for (int i = 0; i < Cantidad; i++) {
        Arreglo_nodos[i] = Temp;
        Temp = Temp->getSiguiente();
    }

    // intercambiamos solo la info
    for (int i = Cantidad - 1; i > 0; --i) {
        int j = rand() % (i + 1); // indice aleatorio
        
        // Intercambiamos la struct Cancion entre los dos nodos
        Cancion Cancion_temporal = Arreglo_nodos[i]->getCancion();
        Arreglo_nodos[i]->setCancion(Arreglo_nodos[j]->getCancion());
        Arreglo_nodos[j]->setCancion(Cancion_temporal);
    }

    // Liberamos la memoria del arreglo  para evitar fugas
    delete[] Arreglo_nodos;
}

void ListaDoble::Mostrarpendientes() {
    // Si no hay cancion actual o es la ultima, mostramos "Vacia" como pide la pauta
    if (actual == nullptr || actual->getSiguiente() == nullptr) {
        cout << "Vacia\n";
        return;
    }

    NodoDoble* Temp = actual->getSiguiente();
    int Posicion = 1;
    
    while (Temp != nullptr) {
        cout << Posicion << ". " << Temp->getCancion().nombre << " - " << Temp->getCancion().artista << "\n";
        Temp = Temp->getSiguiente();
        Posicion++;
    }
}

void ListaDoble::Saltarpistas(int saltos) {
    if (actual == nullptr) return;
    
    //avanzamos el puntero 'actual' la cantidad de saltos solicitados
    for (int i = 0; i < saltos; i++) {
        if (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        } else {
            // Si nos piden saltar mas alla del final, nos quedamos en la ultima
            break; 
        }
    }
}
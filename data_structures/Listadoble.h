#ifndef LISTADOBLE_H
#define LISTADOBLE_H

#include "NodoDoble.h"

struct ListaDoble {

    NodoDoble* cabeza;  //primera canción
    NodoDoble* cola;    //ultima canción 
    NodoDoble* actual;  //canción que está sonando 

    //Constructor y Destructor
    ListaDoble();
    ~ListaDoble();

    //metodos principales
    
    void siguientePista(int repeticion, bool aleatorio);
    void pistaAnterior(int repeticion, bool aleatorio);

    
    //Para que el main sepa qué mostrar 
    Cancion* obtenerActual(); 
    bool tieneActual();

    void Mostrarcoladesdeactual();
   
    void Mostrarlistadocompleto();
    void Fijarporid(int Id_buscado);

    int Obtenerultimoid();
    void Agregaralfinal(Cancion Nueva_cancion);
    Cancion* Buscarporid(int id_buscado);
    bool Eliminarnodo(int id_borrar);
    void Mezclarrestantes();
    
    void Mostrarpendientes();
    void Saltarpistas(int saltos);

   
};

#endif
#ifndef CANCION_H
#define CANCION_H

#include <string> 
using namespace std;

struct Cancion {
    int id;
    string nombre;
    string artista;
    string album;
    int year; 
    int duracion;
    string ubicacion;
    
    // Constructor con parámetros 
    Cancion(int id_cancion, string nombre_cancion, string nombre_artista, string nombre_album, int yearr, int duracion_segundos, string ubicacion_cancion) {
        id = id_cancion;
        nombre = nombre_cancion;
        artista = nombre_artista;
        album = nombre_album;
        year = yearr;
        duracion = duracion_segundos;
        ubicacion = ubicacion_cancion;
    }

    // Constructor vacio
    Cancion() {
        id = 0;
        nombre = "Desconocido";
        artista = "Desconocido";
        album = "Desconocido";
        year = 0;
        duracion = 0;
        ubicacion = "";
    }
};

#endif
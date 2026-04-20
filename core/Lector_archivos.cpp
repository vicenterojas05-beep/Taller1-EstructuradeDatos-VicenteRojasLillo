#include "lector_archivos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void cargarCanciones(ListaDoble& listaReproduccion) {
    // Abrimos el archivo 
    ifstream archivo("music_source.txt"); 

    if (!archivo.is_open()) {
        cout << "Advertencia: No se encontro music_source.txt. Iniciando reproductor con lista vacia.\n";
        return;
    }

    string linea;
    int contador = 0; // Para saber cuantas canciones cargamos

    // Leemos linea por linea hasta el final del archivo
    while (getline(archivo, linea)) {
        // por si hay lineas vacias
        if (linea.empty()) continue;

        stringstream ss(linea);
        string token;
        Cancion nuevaCancion;

        // Extraemos cada dato según el formato del enunciado:
        // id_interno, nombre_cancion, nombre_artista, nombre_album, año, duración, ubicacion
        
        getline(ss, token, ',');
        nuevaCancion.id = stoi(token);

        getline(ss, nuevaCancion.nombre, ',');
        getline(ss, nuevaCancion.artista, ',');
        getline(ss, nuevaCancion.album, ',');
        
        getline(ss, token, ',');
        nuevaCancion.year = stoi(token);

        getline(ss, token, ',');
        nuevaCancion.duracion = stoi(token);

        getline(ss, nuevaCancion.ubicacion, ','); // El último dato hasta la próxima coma o salto de línea

        // Agregamos la canción armada a la lista doblemente enlazada
        listaReproduccion.agregarAlFinal(nuevaCancion);
        contador++;
    }

    archivo.close();
    cout << ">> Exito: Se cargaron " << contador << " canciones desde music_source.txt.\n";
}
#include <iostream>
using namespace std;
#include <string>


void Mostrarmenuprincipal(string estado, string cancion, string artista, string album, int year, string modoaleatorio, string modorepeticion) {
    cout << "========================================================\n";
    cout << estado << " (" << modoaleatorio << "-" << modorepeticion << "): " << cancion << "\n";
    cout << "Artista: " << artista << "\n";
    cout << "Album: " << album << " (" << year << ")\n";
    cout << "========================================================\n";
    cout << "Opciones:\n";
    cout << "W - Reproducir/Pausar\n";
    cout << "Q - Pista Anterior\n";
    cout << "E - Pista Siguiente\n";
    cout << "S - Activar/Desactivar modo aleatorio\n";
    cout << "R - Repeticion (Desactivado/Repetir una/Repetir todas)\n";
    cout << "A - Ver lista de reproduccion actual\n";
    cout << "L - Listado de canciones\n";
    cout << "X - Salir\n";
    cout << "Ingrese Opcion: ";
}





int main() {
    //variables de estado
   
    string estado_actual = "Reproduccion Detenida"; 
    string cancion_actual = "Ninguna";
    string artista_actual = "N/A";
    string album_actual = "N/A";
    int year_actual = 0;
    string aleatorio = "";
    string repeticion = "";

    string opcion;
    bool ejecutando = true;

    //2.aqui iria la carga de datos (music_source.txt y status.cfg)
    //cargarDatos(); o algo asi

    //3.el ciclo principal del programa
    while (ejecutando) {
        
        //limpiar la consola para ganar 1 decima extra 
        #ifdef _WIN32
            system("cls");
        #else
           
        #endif

        //mostrar la interfaz
        Mostrarmenuprincipal(estado_actual, cancion_actual, artista_actual, album_actual, year_actual, aleatorio, repeticion);

        //leer la opción del usuario
        cin >> opcion;

        //convertir la opción a mayúscula para evitar errores si el usuario ingresa 'w' en vez de 'W'
        if (opcion.length() > 0) {
            opcion[0] = toupper(opcion[0]);
        }

        //4.evaluar la opción elegida
        if (opcion == "W") {
             cout << ">> Funcion: Reproducir/Pausar\n";
             
        } 
        else if (opcion == "Q") {
             cout << ">> Funcion: Pista Anterior\n";
             
        } 
        else if (opcion == "E") {
             cout << ">> Funcion: Pista Siguiente\n";
             
        }
        else if (opcion == "S") {
             cout << ">> Funcion: Modo Aleatorio\n";
             
        }
        else if (opcion == "R") {
             cout << ">> Funcion: Repeticion\n";
             
        }
        else if (opcion == "A") {
             cout << ">> Abriendo Submenu: Lista Actual\n";
             // abrirSubmenuListaActual();
        }
        else if (opcion == "L") {
             cout << ">> Abriendo Submenu: Todas las canciones\n";
             // abrirSubmenuListadoCompleto();
        }
        else if (opcion == "X") {
             cout << ">> Guardando estado y saliendo del reproductor...\n";
             // guardarEstado();
             ejecutando = false;
        } 
        else {
             cout << ">> Opcion no valida. Intente nuevamente.\n";
        }

        //pausa temporal para ver el mensaje antes de limpiar la pantalla de nuevo
        if (ejecutando) {
            cout << "Presione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    }

    return 0;

};
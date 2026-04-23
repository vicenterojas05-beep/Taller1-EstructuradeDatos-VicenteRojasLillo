#include <iostream>
using namespace std;
#include <string>
#include "data_structures/Listadoble.h"



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
   
    string estado_actual = "Reproduccion detenida"; 
    string cancion_actual = "Ninguna";
    string artista_actual = "N/A";
    string album_actual = "N/A";
    int year_actual = 0;
    string aleatorio = "";
    string repeticion = "";

    string opcion;
    bool ejecutando = true;

    ListaDoble miLista;

    // --- INICIO DE DATOS DE PRUEBA (Borrar cuando hagamos el Lector de Archivos) ---
    Cancion c1(1, "Bohemian Rhapsody", "Queen", "A Night at the Opera", 1975, 354, "ruta1");
    Cancion c2(2, "Tren al Sur", "Los Prisioneros", "Corazones", 1990, 334, "ruta2");
    Cancion c3(3, "Shape of You", "Ed Sheeran", "Divide", 2017, 233, "ruta3");
    Cancion c4(4, "Blinding Lights", "The Weeknd", "After Hours", 2020, 200, "ruta4");
    Cancion c5(5, "Mira Niñita", "Los Jaivas", "Todos Juntos", 1972, 412, "ruta5");

    miLista.agregarAlFinal(c1);
    miLista.agregarAlFinal(c2);
    miLista.agregarAlFinal(c3);
    miLista.agregarAlFinal(c4);
    miLista.agregarAlFinal(c5);

    //esto es para que cuando el programa inicie no muestre el menu con datos como "ninguna" o "N/A"
    if (miLista.tieneActual()) {
        Cancion* c = miLista.obtenerActual();
        cancion_actual = c->nombre;
        artista_actual = c->artista;
        album_actual = c->album;
        year_actual = c->year;
    }
    // --- FIN DE DATOS DE PRUEBA ---

    //aqui iria la carga de datos (music_source.txt y status.cfg)
    //cargarDatos(); o algo asi

    //el ciclo principal del programa
    while (ejecutando) {
        
        //limpiar la consola para la decima extra 
        #ifdef _WIN32
            system("cls");
        #else
           
        #endif

        //mostrar la interfaz
        Mostrarmenuprincipal(estado_actual, cancion_actual, artista_actual, album_actual, year_actual, aleatorio, repeticion);

        //leer la opción del usuario
        cin >> opcion;

        //convertir la opción a mayuscula para evitar errores si el usuario ingresa 'w' en vez de 'W'
        if (opcion.length() > 0) {
            opcion[0] = toupper(opcion[0]);
        }
        // actualizar la información que se muestra en el menu
        if (miLista.tieneActual()) {
            Cancion* c = miLista.obtenerActual();
            cancion_actual = c->nombre;
            artista_actual = c->artista;
            album_actual = c->album;
            year_actual = c->year;
          }
    

        //evaluar la opción elegida
        if (opcion == "W") {
          if(!miLista.tieneActual()){
               cout << ">> No hay canciones para reproducir.\n";
          }
          else{
               if (estado_actual == "En pausa" || estado_actual== "Reproduccion detenida") { //si estaba en pausa o es la primera vez que se
                    estado_actual = "Reproduciendo";                                          // inicia, se cambia a reproduciendo
               }
              else{
               estado_actual = "En pausa"; // y viceversa, si estaba reproduciendo se pone en pausa
              } 
          }
     } 
        else if (opcion == "Q") { //si la opcion es Q la cancion actual se cambia por la cancion anterior (esto dentro de miLista)
          miLista.pistaAnterior();
          } 
        else if (opcion == "E") {
          miLista.siguientePista(); //lo mismo pero con la cancion siguiente
          }
             
        
        else if (opcion == "S") {
             cout << ">> Funcion: Modo Aleatorio\n";
          }
        else if (opcion == "R") {
             cout << ">> Funcion: Repeticion\n";
             
        }
        else if (opcion == "A") {
            bool enSubmenuA = true;
            string opcionA;

            while (enSubmenuA) {
                //limpiamos la pantalla
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif

                //imprimimos el encabezado
                cout << "========================================================\n";
                cout << "REPRODUCCION ACTUAL\n";
                cout << "Sonando ahora: " << cancion_actual << " - " << artista_actual << "\n";
                cout << "========================================================\n";

                //llamamos al nuevo metodo
                miLista.Mostrarcoladesdeactual();

                //se muestra las opciones del menu
                cout << "Opciones:\n";
                cout << "S<num> - Saltar a pista especifica (Ej: S2)\n";
                cout << "V - Volver al menu principal\n";
                cout << "Ingrese Opcion: ";
                
                cin >> opcionA;

                if (opcionA.length() > 0) opcionA[0] = toupper(opcionA[0]);

                //evaluamos que hacer
                if (opcionA == "V") {
                    enSubmenuA = false; //rompemos este while y volvemos al principal
                } 
                else if (opcionA[0] == 'S') { 
                    if (opcionA.length() > 1) {
                        int cantidad_saltos = 0;
                        bool es_numero_valido = true;

                        //recorremos la palabra desde la posición 1 para saltarnos la 'S'
                        for (int i = 1; i < opcionA.length(); i++) {
                            //verificamos que el caracter sea realmente un numero
                            if (opcionA[i] >= '0' && opcionA[i] <= '9') {
                                // Restar '0' convierte el texto a numero
                                int digito = opcionA[i] - '0';
                                
                                //multiplicar por 10 es para armar numeros de 2 cifras (ej: si escriben S12)
                                cantidad_saltos = (cantidad_saltos * 10) + digito;
                            } else {
                                es_numero_valido = false; //escribieron una letra por error
                                break;
                            }
                        }

                        if (es_numero_valido && cantidad_saltos > 0) {
                            miLista.Saltarpistas(cantidad_saltos);
                            
                            //actualizamos la información de la pantalla
                            if (miLista.tieneActual()) {
                                Cancion* c = miLista.obtenerActual();
                                cancion_actual = c->nombre;
                                artista_actual = c->artista;
                                album_actual = c->album;
                                year_actual = c->year; 
                            }
                        } else {
                            cout << ">>error solo numeros despues de la S.\n";
                        }
                    } else {
                        cout << ">> error Faltan numeros despues de la S.\n";
                    }

                    cout << "Presione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                }
                else {
                    cout << ">> Opcion no valida.\n";
                    cout << "Presione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                }
            }
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
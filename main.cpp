#include <iostream>
using namespace std;
#include <string>
#include "data_structures/Listadoble.h"
#include <fstream>
#include <sstream>




void Mostrarmenuprincipal(string estado, string cancion, string artista, string album, int year, string modoaleatorio, string repeticion) {
   
    cout << "========================================================\n";
    cout << estado << " (" << modoaleatorio << "-" << repeticion << "): " << cancion << "\n";
    cout << "Artista: " << artista << "\n";
    cout << "Album: " << album << " (" << year << ")\n";
    cout << "========================================================\n";
    cout << "Opciones:\n";
    cout << "W - Reproducir/Pausar\n";
    cout << "Q - Pista Anterior\n";
    cout << "E - Pista Siguiente\n";
    cout << "S - Activar/Desactivar modo aleatorio\n";
    cout << "R - Repeticion \n";
    cout << "A - Ver lista de reproduccion actual\n";
    cout << "L - Listado de canciones\n";
    cout << "X - Salir\n";
    cout << "Ingrese Opcion: ";
}


void Cargardatos(ListaDoble& lista) {
    //abrimos el archivo
    ifstream archivo("music_source.txt");
    
    // por si el archivo esta mal escrito o no existe
    if (!archivo.is_open()) {
        cout << ">> Advertencia: No se encontro music_source.txt. Iniciando con lista vacia.\n";
        return;
    }

    string linea;
    
    //mientras haya lineas por leer  las vamos guardando en "linea"
    while (getline(archivo, linea)) {
        stringstream ss(linea); //convertimos la linea para poder cortarla
        string id_str, nombre, artista, album, year_str, duracion_str, ubicacion;

        //extraemos cada pedazo cortando cuando encontremos una coma ','
        getline(ss, id_str, ',');
        getline(ss, nombre, ',');
        getline(ss, artista, ',');
        getline(ss, album, ',');
        getline(ss, year_str, ',');
        getline(ss, duracion_str, ',');
        getline(ss, ubicacion, ',');

        
        int id, year, duracion;
        //convertimos el texto a numero usando stringstream
        stringstream conv_id(id_str);
        conv_id >> id;
        
        stringstream conv_year(year_str);
        conv_year >> year;
        
        stringstream conv_dur(duracion_str);
        conv_dur >> duracion;

        //armamos la cancion con los datos y la metemos a la lista 
        Cancion nueva_cancion(id, nombre, artista, album, year, duracion, ubicacion);
        lista.Agregaralfinal(nueva_cancion);
    }
    
    archivo.close(); //cerramos el archivo al terminar
}


void Guardarestado(Cancion* cancionActual) {
    // ofstream crea  el archivo
    ofstream archivo("status.cfg"); 

    if (!archivo.is_open()) {
        cout << ">> Error: No se pudo crear el archivo de guardado status.cfg\n";
        return;
    }

    // Si hay una cancion sonando guardamos su ID
    if (cancionActual != nullptr) {
        archivo << cancionActual->id << endl;
    } else {
        // Si no habia nada sonando guardamos un 0
        archivo << 0 << endl;
    }

    archivo.close();
    cout << ">> Estado guardado correctamente en status.cfg\n";
}
void Cargarestado(ListaDoble& lista) {
    ifstream Archivo("status.cfg");
    int Id_guardado = 0;

    if (Archivo.is_open()) {
        Archivo >> Id_guardado;
        Archivo.close();

        if (Id_guardado > 0) {
            lista.Fijarporid(Id_guardado);
            cout << ">> Partida cargada: Retomando desde la cancion ID " << Id_guardado << "\n";
        }
    }
}








int main() {
    //variables de estado
   
    string estado_actual = "Reproduccion detenida"; 
    string cancion_actual = "Ninguna";
    string artista_actual = "N/A";
    string album_actual = "N/A";
    int year_actual = 0;
    string aleatorio = "";
    

    string opcion;
    bool ejecutando = true;

    ListaDoble miLista;

    Cargardatos(miLista); //cargamos las canciones

    Cargarestado(miLista); //cargamos la cancion guardada

   // 0 = Desactivado, 1 = R1 (Repetir Una), 2 = RA (Repetir Todas)
    int modo_repeticion = 0;
    string texto_repeticion ="";

    bool modo_aleatorio = false;
    string texto_aleatorio = "Desactivado";

   
    //esto es para que cuando el programa inicie no muestre el menu con datos como "ninguna" o "N/A"
    if (miLista.tieneActual()) {
        Cancion* c = miLista.obtenerActual();
        cancion_actual = c->nombre;
        artista_actual = c->artista;
        album_actual = c->album;
        year_actual = c->year;
    }
   

    //el ciclo principal del programa
    while (ejecutando) {
        
        //limpiar la consola para la decima extra 
        #ifdef _WIN32
            system("cls");
        #else
           
        #endif

      
        if (modo_repeticion == 1) texto_repeticion = "(R1) ";
        else if (modo_repeticion == 2) texto_repeticion = "(RA) ";

        if(modo_aleatorio) texto_aleatorio = "Activado";
        else texto_aleatorio = "Desactivado";

        //mostrar la interfaz
        Mostrarmenuprincipal(estado_actual, cancion_actual, artista_actual, album_actual, year_actual, texto_aleatorio, texto_repeticion);

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
          miLista.pistaAnterior(modo_repeticion,modo_aleatorio);

          if (miLista.tieneActual()) { //actualizamos lo que se ve en el menu
                Cancion* c = miLista.obtenerActual();
                cancion_actual = c->nombre;
                artista_actual = c->artista;
                album_actual = c->album;
                year_actual = c->year;
            }
          } 
        else if (opcion == "E") {
          miLista.siguientePista(modo_repeticion,modo_aleatorio); //lo mismo pero con la cancion siguiente


          if (miLista.tieneActual()) { //actualizamos lo que se ve en el menu
                Cancion* c = miLista.obtenerActual();
                cancion_actual = c->nombre;
                artista_actual = c->artista;
                album_actual = c->album;
                year_actual = c->year;
            }
          }
             
        
        else if (opcion == "S") {
            modo_aleatorio = !modo_aleatorio; //cambia de true a false o viceversa

            if (modo_aleatorio) {
                //mezcla las pistas restantes una sola vez al activarse
                miLista.Mezclarrestantes();
                cout << ">> Modo aleatorio ACTIVADO. Canciones restantes mezcladas.\n";
            } else {
                // Al desactivar, mantiene la lista en su estado actual
                cout << ">> Modo aleatorio DESACTIVADO.\n";
            }
          }
        else if (opcion == "R") {
            modo_repeticion++;
            if (modo_repeticion > 2) {
                modo_repeticion = 0;
            }
             
        }
        else if (opcion == "A") {
            bool En_submenu_a = true;
            string Opcion_sub;

            while (En_submenu_a) {
                //limpiamos la consola
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif

               
                cout << "Actual " << aleatorio << texto_repeticion << ": " << cancion_actual << " - " << artista_actual << "\n";
                cout << "Lista de reproduccion actual:\n";
                
                //imprimimos las pistas restantes o "Vacia"
                miLista.Mostrarpendientes();

                //menu de opciones
                cout << "\nOpciones:\n";
                cout << "S<num> - Saltar a la cancion seleccionada\n";
                cout << "V - Volver al menu principal\n";
                cout << "Ingrese Opcion: ";
                cin >> Opcion_sub;

                char Comando = toupper(Opcion_sub[0]);

                if (Comando == 'V') {
                    En_submenu_a = false; //salimos al menu principal
                }
                else if (Comando == 'S') {
                    int Saltos = 0;
                    if (Opcion_sub.length() > 1) {
                        Saltos = stoi(Opcion_sub.substr(1));
                    }
                    
                    if (Saltos > 0) {
                        //hacemos el salto en la memoria
                        miLista.Saltarpistas(Saltos);
                        
                        //actualizamos las variables de la interfaz
                        if (miLista.tieneActual()) {
                            Cancion* c = miLista.obtenerActual();
                            cancion_actual = c->nombre;
                            artista_actual = c->artista;
                            album_actual = c->album;
                            year_actual = c->year;
                        }
                        
                        cout << ">> Saltando a la pista...\n";
                        
                        //em la pauta dice que al saltar vuelve automaticamente al menu principal
                        En_submenu_a = false; 
                    }
                }
                
                //pequeña pausa si no eligio V ni hizo un salto exitoso
                if (En_submenu_a) {
                    cout << "\nPresione Enter para continuar...";
                    cin.ignore(); 
                    cin.get();
                }
            }
        }
        else if (opcion == "L") {
            bool En_submenu_l = true;
            string Opcion_sub;

            while (En_submenu_l) {
                //limpiamos la pantalla
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif

                //imprimimos la cabecera exacta que pide la pauta
                cout << "Actual " << aleatorio << texto_repeticion << ": " << cancion_actual << " " << artista_actual << "\n";
                cout << "Canciones registradas:\n";
                
                // llamamos al metodo que muestra las canciones
                miLista.Mostrarlistadocompleto(); 

                // imprimimos las opciones del submenú
                cout << "\nOpciones:\n";
                cout << "R<num> - Reproducir cancion seleccionada\n";
                cout << "A<num> - Agregar cancion seleccionada al final de la lista\n";
                cout << "N - Agregar cancion al registro\n";
                cout << "D<num> - Eliminar cancion seleccionada\n";
                cout << "V - Volver al menu principal\n";
                cout << "Ingrese Opcion: ";
                cin >> Opcion_sub;

                //procesamos el comando
                char Comando = toupper(Opcion_sub[0]); //extraemos la primera letra (R, A, N, D, V)

                if (Comando == 'V') {
                    En_submenu_l = false; //rompemos el ciclo para volver al main
                } 
                else if (Comando == 'N') {
                    cin.ignore(); // Limpiamos la basura de la memoria del cin anterior
                    Cancion Nueva_cancion;

                    cout << "\n--- REGISTRAR NUEVA CANCION ---\n";
                    cout << "Nombre de la cancion: ";
                    getline(cin, Nueva_cancion.nombre);
                    cout << "Nombre del artista: ";
                    getline(cin, Nueva_cancion.artista);
                    cout << "Nombre del album: ";
                    getline(cin, Nueva_cancion.album);
                    cout << "Anio de lanzamiento: ";
                    cin >> Nueva_cancion.year; 
                    cout << "Duracion en segundos: ";
                    cin >> Nueva_cancion.duracion;
                    cin.ignore(); //limpiamos de nuevo antes del ultimo texto
                    cout << "Ubicacion del archivo: ";
                    getline(cin, Nueva_cancion.ubicacion); 

                    //asignamos un nuevo ID correlativo
                    Nueva_cancion.id = miLista.Obtenerultimoid() + 1;

                    //la guardamos en la lista doble
                    miLista.Agregaralfinal(Nueva_cancion);

                    //La guardamos en music_source.txt
                    // ios::app permite "Añadir" al final del archivo en lugar de sobrescribirlo
                    ofstream Archivo_musica("music_source.txt", ios::app); 
                    if (Archivo_musica.is_open()) {
                        Archivo_musica << Nueva_cancion.id << "," 
                                       << Nueva_cancion.nombre << "," 
                                       << Nueva_cancion.artista << "," 
                                       << Nueva_cancion.album << "," 
                                       << Nueva_cancion.year << "," 
                                       << Nueva_cancion.duracion << "," 
                                       << Nueva_cancion.ubicacion << "\n";
                        Archivo_musica.close();
                        cout << ">> Exito: Cancion agregada al registro y guardada en el archivo.\n";
                    } else {
                        cout << ">> Error: No se pudo abrir music_source.txt.\n";
                    }
                }
                else {
                    //extraemos el numero que viene pegado a la letra ( si es R5, extraemos el 5)
                    int Numero_cancion = 0;
                    if (Opcion_sub.length() > 1) {
                        // substr(1) toma todo el texto desde la segunda posicion en adelante
                        Numero_cancion = stoi(Opcion_sub.substr(1)); 
                    }

                    if (Comando == 'R') {
                        // Reproducir cancion especifica y mezclar el resto
                        Cancion* Cancion_encontrada = miLista.Buscarporid(Numero_cancion);
                        if (Cancion_encontrada != nullptr) {
                            miLista.Fijarporid(Numero_cancion); // Reutilizamos este metodo
                            
                            // Extraemos los datos para la pantalla
                            cancion_actual = Cancion_encontrada->nombre;
                            artista_actual = Cancion_encontrada->artista;
                            estado_actual = "Reproduciendo";
                            
                            // La pauta exigia mezclar las pistas restantes
                            miLista.Mezclarrestantes();
                            cout << ">> Reproduciendo '" << cancion_actual << "' y mezclando canciones restantes...\n";
                            
                            En_submenu_l = false; // Salimos al menu principal despues de elegir
                        } else {
                            cout << ">> Error: Cancion ID " << Numero_cancion << " no encontrada.\n";
                        }
                    }
                    else if (Comando == 'A') {
                        //agregar cancion al final de la lista de reproduccion actual
                        Cancion* Cancion_encontrada = miLista.Buscarporid(Numero_cancion);
                        if (Cancion_encontrada != nullptr) {
                            //reutilizamos el metodo Agregaralfinal, clonando la cancion
                            miLista.Agregaralfinal(*Cancion_encontrada);
                            cout << ">> Cancion '" << Cancion_encontrada->nombre << "' agregada a la cola.\n";
                        } else {
                            cout << ">> Error: Cancion ID " << Numero_cancion << " no encontrada.\n";
                        }
                    }
                    else if (Comando == 'D') {
                        //eliminar cancion tanto en memoria como en disco
                        if (miLista.Eliminarnodo(Numero_cancion)) {
                            cout << ">> Cancion ID " << Numero_cancion << " eliminada de la memoria.\n";
                            
                            //reescribimos todo el archivo music_source.txt
                            ofstream Archivo_salida("music_source.txt", ios::trunc); // trunc borra el archivo y lo recrea
                            if (Archivo_salida.is_open()) {
                                NodoDoble* Temp_recorrido = miLista.cabeza; //accedemos a la cabeza para recorrer
                                while (Temp_recorrido != nullptr) {
                                    Archivo_salida << Temp_recorrido->getCancion().id << "," 
                                                   << Temp_recorrido->getCancion().nombre << "," 
                                                   << Temp_recorrido->getCancion().artista << "," 
                                                   << Temp_recorrido->getCancion().album << "," 
                                                   << Temp_recorrido->getCancion().year << "," 
                                                   << Temp_recorrido->getCancion().duracion << "," 
                                                   << Temp_recorrido->getCancion().ubicacion << "\n";
                                    Temp_recorrido = Temp_recorrido->getSiguiente();
                                }
                                Archivo_salida.close();
                                cout << ">> Archivo music_source.txt actualizado.\n";
                            }
                        } else {
                            cout << ">> Error: No se encontro la cancion ID " << Numero_cancion << " para eliminar.\n";
                        }
                    }
                }

                //pausa antes de limpiar la pantalla de nuevo (excepto si eligio v)
                if (Comando != 'V') {
                    cout << "\nPresione Enter para continuar...";
                    cin.ignore(); 
                    cin.get();
                }
            }
        }
        else if (opcion == "X") {
            cout << ">> Guardando estado y saliendo del reproductor...\n";
            
            // obtenemos la cancion actual 
            Cancion* actual = nullptr;
            if (miLista.tieneActual()) {
                actual = miLista.obtenerActual();
            }
            
            // llamamos a la funcion 
            Guardarestado(actual);
            
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
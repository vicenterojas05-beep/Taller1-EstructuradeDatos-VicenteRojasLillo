#include <string>
using namespace std;
struct Cancion
{
     int id;
    string nombre;
    string artista;
    string album;
    int year; //no tengo la letra que viene despues de la n en el abecedario en mi teclado
    int duracion;
    string ubicacion;
    
    Cancion(int id_cancion, string nombre_cancion, string nombre_artista,string nombre_album 
        ,int yearr,int duracion_segundos,string ubicacion_cancion);
};
 
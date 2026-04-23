
#define NODO_DOBLE_H
#include "../classes/Cancion.h"
#include <string>
using namespace std;

class NodoDoble {
private:
    Cancion cancion;      
    NodoDoble* siguiente;
    NodoDoble* anterior; // para retroceder a la cancion anterior

public:
    // Constructor
    NodoDoble(Cancion c);

    // getters
    Cancion& getCancion();
    NodoDoble* getSiguiente();
    NodoDoble* getAnterior();

    // setters
    void setCancion(Cancion song);
    void setSiguiente(NodoDoble* nodo);
    void setAnterior(NodoDoble* nodo);
};


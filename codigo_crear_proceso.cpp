#include <iostream>
#include <string>
using namespace std;

struct Proceso {
    int id;
    string nombre;
    int prioridad;
    Proceso* siguiente;
};

struct Lista {
    Proceso* inicio;
    Proceso* fin;
    int siguienteID;
};

void inicializarLista(Lista& lista) {
    lista.inicio = nullptr;
    lista.fin = nullptr;
    lista.siguienteID = 1;
}

Proceso* crearProceso(Lista& lista, string nombre, int prioridad) {
    Proceso* nuevo = new Proceso{ lista.siguienteID++, nombre, prioridad, nullptr };
    if (!lista.inicio)
        lista.inicio = lista.fin = nuevo;
    else {
        lista.fin->siguiente = nuevo;
        lista.fin = nuevo;
    }
    return nuevo;
}

Proceso* buscarProceso(Lista& lista, int id) {
    Proceso* actual = lista.inicio;
    while (actual) {
        if (actual->id == id) return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

bool eliminarProceso(Lista& lista, int id) {
    Proceso* actual = lista.inicio;
    Proceso* anterior = nullptr;
    while (actual) {
        if (actual->id == id) {
            if (anterior)
                anterior->siguiente = actual->siguiente;
            else
                lista.inicio = actual->siguiente;
            if (actual == lista.fin)
                lista.fin = anterior;
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}

void mostrarLista(Lista& lista) {
    Proceso* actual = lista.inicio;
    while (actual) {
        cout << "ID: " << actual->id << ", Nombre: " << actual->nombre << ", Prioridad: " << actual->prioridad << "\n";
        actual = actual->siguiente;
    }
}

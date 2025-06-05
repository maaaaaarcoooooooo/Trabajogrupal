#include <iostream>
using namespace std;

struct NodoPila {
    int idProceso;
    NodoPila* siguiente;
};

void push(NodoPila*& cima, int idProceso) {
    NodoPila* nuevo = new NodoPila{ idProceso, cima };
    cima = nuevo;
}

int pop(NodoPila*& cima) {
    if (!cima) return -1;
    int id = cima->idProceso;
    NodoPila* temp = cima;
    cima = cima->siguiente;
    delete temp;
    return id;
}

bool pilaVacia(NodoPila* cima) {
    return cima == nullptr;
}

void mostrarPila(NodoPila* cima) {
    while (cima) {
        cout << "ID Proceso: " << cima->idProceso << endl;
        cima = cima->siguiente;
    }
}

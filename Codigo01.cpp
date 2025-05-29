#include <iostream>
#include <string>
using namespace std;

const int MAX_PROCESOS = 100;

struct Proceso {
    int id;
    string nombre;
    string estado;
    int siguiente;
};

Proceso procesos[MAX_PROCESOS];
int cantidad = 0;
int inicioLista = -1;

int cola[MAX_PROCESOS];
int frente = 0;
int final = -1;

int pila[MAX_PROCESOS];
int tope = -1;

void agregarProceso(string nombre) {
    if (cantidad >= MAX_PROCESOS) {
        cout << "Límite de procesos alcanzado.\n";
        return;
    }

    procesos[cantidad].id = cantidad + 1;
    procesos[cantidad].nombre = nombre;
    procesos[cantidad].estado = "Creado";
    procesos[cantidad].siguiente = -1;

    if (inicioLista == -1) {
        inicioLista = cantidad;
    } else {
        int actual = inicioLista;
        while (procesos[actual].siguiente != -1)
            actual = procesos[actual].siguiente;
        procesos[actual].siguiente = cantidad;
    }

    cout << "Proceso creado: " << nombre << " (ID " << procesos[cantidad].id << ")\n";
    cantidad++;
}

void mostrarLista() {
    if (inicioLista == -1) {
        cout << "No hay procesos.\n";
        return;
    }

    cout << "Lista de Procesos:\n";
    int actual = inicioLista;
    while (actual != -1) {
        cout << "ID: " << procesos[actual].id
             << ", Nombre: " << procesos[actual].nombre
             << ", Estado: " << procesos[actual].estado << endl;
        actual = procesos[actual].siguiente;
    }
}

int buscarProceso(int idBuscado) {
    for (int i = 0; i < cantidad; i++) {
        if (procesos[i].id == idBuscado)
            return i;
    }
    return -1;
}

void encolar(int indice) {
    if (final + 1 >= MAX_PROCESOS) {
        cout << "Cola llena.\n";
        return;
    }

    final++;
    cola[final] = indice;
    procesos[indice].estado = "Listo";
    cout << "Proceso encolado: " << procesos[indice].nombre << endl;
}


void apilar(int indice) {
    if (tope + 1 >= MAX_PROCESOS) {
        cout << "Pila llena.\n";
        return;
    }

    tope++;
    pila[tope] = indice;
    procesos[indice].estado = "Terminado";
    cout << "Proceso terminado: " << procesos[indice].nombre << endl;
}
 

int main() {
    int opcion;
    string nombre;
    int id;

    do {
        cout << "\n Menu:\n";
        cout << "1. Crear proceso\n";
        cout << "2. Ver lista de procesos\n";
        cout << "3. Encolar proceso por ID\n";
        cout << " Ejecutar siguiente proceso\n";
        cout << " Ver historial de procesos terminados\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Nombre del proceso: ";
            cin >> nombre;
            agregarProceso(nombre);
        } else if (opcion == 2) {
            mostrarLista();
        } else if (opcion == 3) {
            cout << "ID del proceso: ";
            cin >> id;
            int idx = buscarProceso(id);
            if (idx != -1) {
                encolar(idx);
            } else {
                cout << "Proceso no encontrado.\n";
            }
       
        } else if (opcion != 0) {
            cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    cout << "Saliendo del sistema...\n";
    return 0;
}

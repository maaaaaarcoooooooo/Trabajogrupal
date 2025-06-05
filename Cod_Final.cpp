#include <iostream>
#include <string>

using namespace std;

// ==== Estructura de un proceso ====
struct Proceso {
    int id;
    string nombre;
    int prioridad;
    Proceso* siguiente;
};

// ==== Lista de procesos ====
struct Lista {
    Proceso* inicio;
    Proceso* fin;
    int siguienteID;
};

// ==== Cola FIFO ====
struct NodoCola {
    Proceso* proceso;
    NodoCola* siguiente;
};

struct Cola {
    NodoCola* frente;
    NodoCola* final;
};

// ==== Pila LIFO ====
struct NodoPila {
    int idProceso;
    NodoPila* siguiente;
};

// ==== Funciones Lista ====
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
    cout << "Proceso creado con ID: " << nuevo->id << endl;
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
    cout << "\nProcesos registrados:\n";
    while (actual) {
        cout << "ID: " << actual->id << ", Nombre: " << actual->nombre << ", Prioridad: " << actual->prioridad << "\n";
        actual = actual->siguiente;
    }
}

// ==== Cola ====
void inicializarCola(Cola& cola) {
    cola.frente = cola.final = nullptr;
}

void encolar(Cola& cola, Proceso* p) {
    NodoCola* nuevo = new NodoCola{ p, nullptr };
    if (!cola.frente) cola.frente = cola.final = nuevo;
    else {
        cola.final->siguiente = nuevo;
        cola.final = nuevo;
    }
}

Proceso* desencolar(Cola& cola) {
    if (!cola.frente) return nullptr;
    NodoCola* temp = cola.frente;
    Proceso* p = temp->proceso;
    cola.frente = cola.frente->siguiente;
    if (!cola.frente) cola.final = nullptr;
    delete temp;
    return p;
}

bool colaVacia(Cola& cola) {
    return cola.frente == nullptr;
}

// ==== Pila ====
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
    cout << "\nMemoria (Pila):\n";
    while (cima) {
        cout << "ID Proceso: " << cima->idProceso << endl;
        cima = cima->siguiente;
    }
}

// ==== MAIN ====
int main() {
    Lista lista;
    Cola cola;
    NodoPila* pila = nullptr;

    inicializarLista(lista);
    inicializarCola(cola);

    int opcion;
    do {
        cout << "\n=== GESTION DE PROCESOS ===\n";
        cout << "1. Crear Proceso\n";
        cout << "2. Eliminar Proceso\n";
        cout << "3. Buscar Proceso\n";
        cout << "4. Actualizar Prioridad\n";
        cout << "5. Asignar Memoria (Push)\n";
        cout << "6. Liberar Memoria (Pop)\n";
        cout << "7. Ver Procesos\n";
        cout << "8. Ejecutar Procesos (CPU)\n";
        cout << "9. Ver Memoria\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            string nombre;
            int prioridad;
            cout << "Nombre del proceso: ";
            cin >> nombre;
            cout << "Prioridad: ";
            cin >> prioridad;
            crearProceso(lista, nombre, prioridad);
        }
        else if (opcion == 2) {
            int id;
            cout << "ID del proceso a eliminar: ";
            cin >> id;
            if (eliminarProceso(lista, id))
                cout << "Proceso eliminado.\n";
            else
                cout << "Proceso no encontrado.\n";
        }
        else if (opcion == 3) {
            int id;
            cout << "ID del proceso a buscar: ";
            cin >> id;
            Proceso* p = buscarProceso(lista, id);
            if (p)
                cout << "Encontrado: " << p->nombre << " con prioridad " << p->prioridad << endl;
            else
                cout << "Proceso no encontrado.\n";
        }
        else if (opcion == 4) {
            int id, nuevaPrioridad;
            cout << "ID del proceso: ";
            cin >> id;
            cout << "Nueva prioridad: ";
            cin >> nuevaPrioridad;
            Proceso* p = buscarProceso(lista, id);
            if (p) {
                p->prioridad = nuevaPrioridad;
                cout << "Prioridad actualizada.\n";
            } else {
                cout << "Proceso no encontrado.\n";
            }
        }
        else if (opcion == 5) {
            int id;
            cout << "ID del proceso a cargar en memoria: ";
            cin >> id;
            Proceso* p = buscarProceso(lista, id);
            if (p) {
                push(pila, id);
                cout << "Proceso cargado en pila.\n";
            } else {
                cout << "Proceso no encontrado.\n";
            }
        }
        else if (opcion == 6) {
            int id = pop(pila);
            if (id != -1)
                cout << "Proceso ID " << id << " liberado de la memoria.\n";
            else
                cout << "Memoria vacia.\n";
        }
        else if (opcion == 7) {
            mostrarLista(lista);
        }
        else if (opcion == 8) {
            Proceso* actual = lista.inicio;
            while (actual) {
                encolar(cola, actual);
                actual = actual->siguiente;
            }

            while (!colaVacia(cola)) {
                Proceso* p = desencolar(cola);
                cout << "\nEjecutando proceso ID " << p->id << ": " << p->nombre << endl;
                char respuesta;
                cout << "¿Termino el proceso? (s/n): ";
                cin >> respuesta;

                if (respuesta == 's' || respuesta == 'S') {
                    eliminarProceso(lista, p->id);
                    int id = pop(pila);
                    cout << "Memoria liberada para proceso " << id << endl;
                } else {
                    encolar(cola, p);
                }
            }
        }
        else if (opcion == 9) {
            mostrarPila(pila);
        }

    } while (opcion != 0);

    cout << "Saliendo del sistema.\n";
    return 0;
}

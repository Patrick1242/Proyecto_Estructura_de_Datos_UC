#include <iostream>
#include <string>
using namespace std;

struct Cliente {
    int id;
    string nombre;
    string contacto;
    Cliente* siguiente; 
};

Cliente* cabezaClientes = NULL;

void registrarCliente(int id, string nombre, string contacto) {
    Cliente* nuevo = new Cliente;
    nuevo->id = id;
		nuevo->nombre = nombre;
		nuevo->contacto = contacto;
		nuevo->siguiente = NULL;

    if (cabezaClientes == NULL) {
        cabezaClientes = nuevo;
    } else {
        Cliente* temp = cabezaClientes;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }
    cout << "Cliente registrado: " << nombre << endl;
}
void mostrarClientes() {
    Cliente* temp = cabezaClientes;
    if (temp == NULL) {
        cout << "No hay clientes registrados.\n";
        return;
    }
    cout << "\n--- Lista de Clientes ---\n";
    while (temp != NULL) {
        cout << "ID: " << temp->id << " | Nombre: " << temp->nombre << " | Contacto: " << temp->contacto << endl;
        temp = temp->siguiente;
    }
}

struct Servicio {
    int id;
    string tipo;
    int prioridad; 
    Servicio* siguiente;
};

Servicio* frenteServicios = NULL;

   
void encolarServicio(int id, string tipo, int prioridad) {
    Servicio* nuevo = new Servicio{id, tipo, prioridad, NULL};

       
    if (frenteServicios == NULL || prioridad < frenteServicios->prioridad) {
        nuevo->siguiente = frenteServicios;
        frenteServicios = nuevo;
    } else {
        Servicio* temp = frenteServicios;
        while (temp->siguiente != NULL && temp->siguiente->prioridad <= prioridad) {
            temp = temp->siguiente;
        }
        nuevo->siguiente = temp->siguiente;
        temp->siguiente = nuevo;
    }
    cout << "Servicio agregado: " << tipo << " (Prioridad " << prioridad << ")\n";
}

void ejecutarServicio() {
    if (frenteServicios == NULL) {
        cout << "No hay servicios pendientes.\n";
        return;
    }
    Servicio* temp = frenteServicios;
    frenteServicios = frenteServicios->siguiente;
    cout << "Ejecutando servicio ID " << temp->id << ": " << temp->tipo << endl;
    delete temp;
}

void mostrarServicios() {
    if (frenteServicios == NULL) {
        cout << "No hay servicios en cola.\n";
        return;
    }
    Servicio* temp = frenteServicios;
    cout << "\n--- Cola de Servicios (Postventa) ---\n";
    while (temp != NULL) {
        cout << "ID: " << temp->id << " | Tipo: " << temp->tipo << " | Prioridad: " << temp->prioridad << endl;
        temp = temp->siguiente;
    }
}

struct Repuesto {
    int id;
    string nombre;
    Repuesto* abajo; // apunta al elemento anterior
};
Repuesto* cimaRepuestos = NULL;

void agregarRepuesto(int id, string nombre) {
    Repuesto* nuevo = new Repuesto{id, nombre, cimaRepuestos};
    cimaRepuestos = nuevo;
    cout << "Repuesto agregado: " << nombre << endl;
}

void usarRepuesto() {
    if (cimaRepuestos == NULL) {
        cout << "No hay repuestos disponibles.\n";
        return;
    }
    Repuesto* temp = cimaRepuestos;
    cimaRepuestos = cimaRepuestos->abajo;
    cout << "Usando repuesto: " << temp->nombre << endl;
    delete temp;
}

void mostrarRepuestos() {
    if (cimaRepuestos == NULL) {
        cout << "Inventario vacío.\n";
        return;
    }
    Repuesto* temp = cimaRepuestos;
    cout << "\n--- Pila de Repuestos ---\n";
    while (temp != NULL) {
        cout << "ID: " << temp->id << " | Nombre: " << temp->nombre << endl;
        temp = temp->abajo;
    }
}

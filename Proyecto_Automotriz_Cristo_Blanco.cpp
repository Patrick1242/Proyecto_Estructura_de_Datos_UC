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

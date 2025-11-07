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
int main() {
    int opcion;
    do {
        system("cls"); // Windows; usa "clear" en Linux/Mac
        cout << "==================================================\n";
        cout << "||     SISTEMA DE GESTION AUTOMOTRIZ            ||\n";
        cout << "==================================================\n";
        cout << "|| 1. Registrar cliente (Ventas)                ||\n";
        cout << "|| 2. Mostrar clientes                          ||\n";
        cout << "|| 3. Agregar servicio (Postventa)              ||\n";
        cout << "|| 4. Mostrar servicios                         ||\n";
        cout << "|| 5. Ejecutar servicio                         ||\n";
        cout << "|| 6. Agregar repuesto (Servicio Tecnico)       ||\n";
        cout << "|| 7. Mostrar repuestos                         ||\n";
        cout << "|| 8. Usar repuesto                             ||\n";
        cout << "|| 9. Salir                                     ||\n";
        cout << "==================================================\n";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1: {
                int id;
                string nombre, contacto;
                cout << "ID Cliente: "; cin >> id;
                cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Contacto: "; getline(cin, contacto);
                registrarCliente(id, nombre, contacto);
                break;
            }
            case 2:
                mostrarClientes();
                break;
            case 3: {
                int id, prioridad;
                string tipo;
                cout << "ID Servicio: "; cin >> id;
                cin.ignore();
                cout << "Tipo de servicio: "; getline(cin, tipo);
                cout << "Prioridad (1=Alta, 2=Media, 3=B_ps): "; cin >> prioridad;
                encolarServicio(id, tipo, prioridad);
                break;
            }
            case 4:
                mostrarServicios();
                break;
            case 5:
                ejecutarServicio();
                break;
            case 6: {
                int id;
                string nombre;
                cout << "ID Repuesto: "; cin >> id;
                cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                agregarRepuesto(id, nombre);
                break;
            }
            case 7:
                mostrarRepuestos();
                break;
            case 8:
                usarRepuesto();
                break;
            case 9:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente.\n";
                break;
        }
        
        if (opcion != 9) {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }
        
    } while (opcion != 9);
    return 0;
}

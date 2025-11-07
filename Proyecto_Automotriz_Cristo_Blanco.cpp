#include <iostream>
#include <string>
using namespace std;

// === ESTRUCTURA CLIENTE ===
struct Cliente {
    int id;           // ID numérico único (DNI)
    string nombre;    // Nombre del cliente
    string contacto;  // Teléfono 
    Cliente* siguiente; // Puntero al siguiente nodo en la lista enlazada
};
Cliente* cabezaClientes = NULL; // Apunta al primer cliente (lista vacía al inicio)

// === REGISTRAR CLIENTE ===
// Agrega un nuevo cliente al final de la lista enlazada
void registrarCliente(int id, string nombre, string contacto) {
    Cliente* nuevo = new Cliente; // Crea un nuevo nodo en memoria dinámica
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->contacto = contacto;
    nuevo->siguiente = NULL;

    if (cabezaClientes == NULL) {
        cabezaClientes = nuevo; // Si la lista está vacía, el nuevo es el primero
    } else {
        Cliente* temp = cabezaClientes;
        while (temp->siguiente != NULL) {
            temp = temp->siguiente; // Recorre hasta el último nodo
        }
        temp->siguiente = nuevo; // Enlaza el nuevo nodo al final
    }
    cout << "Cliente registrado: " << nombre << endl;
}

// === MOSTRAR CLIENTES ===
// Recorre e imprime todos los clientes registrados
void mostrarClientes() {
    Cliente* temp = cabezaClientes;
    if (temp == NULL) {
        cout << "No hay clientes registrados.\n";
        return;
    }
    cout << "\n--- Lista de Clientes ---\n";
    while (temp != NULL) {
        cout << "ID: " << temp->id 
             << " | Nombre: " << temp->nombre 
             << " | Contacto: " << temp->contacto << endl;
        temp = temp->siguiente;
    }
}

// === ESTRUCTURA SERVICIO ===
// Cola con prioridad: 1 = alta, 2 = media, 3 = baja
struct Servicio {
    int id;
    string tipo;      
    int prioridad;    // Menor número = mayor prioridad
    Servicio* siguiente;
};
Servicio* frenteServicios = NULL; // Frente de la cola (primer servicio)

// === ENCOLAR SERVICIO ===
// Inserta un servicio ordenado por prioridad (menor número primero)
void encolarServicio(int id, string tipo, int prioridad) {
    Servicio* nuevo = new Servicio{id, tipo, prioridad, NULL};

    if (frenteServicios == NULL || prioridad < frenteServicios->prioridad) {
        nuevo->siguiente = frenteServicios;
        frenteServicios = nuevo; // Inserta al inicio si tiene mayor prioridad
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

// === EJECUTAR SERVICIO ===
// Elimina y ejecuta el servicio de mayor prioridad (frente de la cola)
void ejecutarServicio() {
    if (frenteServicios == NULL) {
        cout << "No hay servicios pendientes.\n";
        return;
    }
    Servicio* temp = frenteServicios;
    frenteServicios = frenteServicios->siguiente;
    cout << "Ejecutando servicio ID " << temp->id << ": " << temp->tipo << endl;
    delete temp; // Libera memoria
}

// === MOSTRAR SERVICIOS ===
// Muestra todos los servicios en orden de prioridad
void mostrarServicios() {
    if (frenteServicios == NULL) {
        cout << "No hay servicios en cola.\n";
        return;
    }
    Servicio* temp = frenteServicios;
    cout << "\n--- Cola de Servicios (Postventa) ---\n";
    while (temp != NULL) {
        cout << "ID: " << temp->id 
             << " | Tipo: " << temp->tipo 
             << " | Prioridad: " << temp->prioridad << endl;
        temp = temp->siguiente;
    }
}

// === ESTRUCTURA REPUESTO ===
// Pila (LIFO): último en entrar, primero en salir
struct Repuesto {
    int id;
    string nombre;
    Repuesto* abajo; // Apunta al repuesto anterior (debajo en la pila)
};
Repuesto* cimaRepuestos = NULL; // Cima de la pila

// === AGREGAR REPUESTO ===
// Empuja un nuevo repuesto a la cima de la pila
void agregarRepuesto(int id, string nombre) {
    Repuesto* nuevo = new Repuesto{id, nombre, cimaRepuestos};
    cimaRepuestos = nuevo;
    cout << "Repuesto agregado: " << nombre << endl;
}

// === USAR REPUESTO ===
// Saca y usa el repuesto de la cima
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

// === MOSTRAR REPUESTOS ===
// Muestra la pila desde la cima hacia abajo
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

// === PROGRAMA PRINCIPAL ===
int main() {
    int opcion;

    do {
        system("cls"); // Limpia pantalla

        // === MENÚ EN CAJA ===
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

            // === REGISTRAR CLIENTE CON VALIDACIÓN ===
            case 1: {
                int id;
                string nombre, contacto;

                // ID: solo números y mayor a 0
                cout << "ID Cliente (solo numeros): ";
                while (!(cin >> id) || id <= 0) {
                    if (!(cin >> id)) {
                        cout << "Error: Ingrese solo numeros: ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    } else {
                        cout << "Error: ID debe ser mayor a 0: ";
                        cin.ignore(10000, '\n');
                    }
                }
                cin.ignore(); // limpia el salto de línea

                // NOMBRE: solo letras y espacios
                cout << "Nombre (solo letras): ";
                while (true) {
                    getline(cin, nombre);
                    if (nombre.empty()) {
                        cout << "Error: No puede estar vacio: ";
                        continue;
                    }
                    bool soloLetras = true;
                    for (char c : nombre) {
                        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
                            soloLetras = false;
                            break;
                        }
                    }
                    if (soloLetras) break;
                    cout << "Error: Solo letras y espacios: ";
                }

                // CONTACTO: solo números y no vacío
                cout << "Contacto (solo numeros): ";
                while (true) {
                    getline(cin, contacto);
                    if (contacto.empty()) {
                        cout << "Error: No puede estar vacio: ";
                        continue;
                    }
                    bool soloNumeros = true;
                    for (char c : contacto) {
                        if (c < '0' || c > '9') {
                            soloNumeros = false;
                            break;
                        }
                    }
                    if (soloNumeros) break;
                    cout << "Error: Solo numeros permitidos: ";
                }

                registrarCliente(id, nombre, contacto);
                break;
            }

            case 2: mostrarClientes(); break;
            case 3: {
                int id, prioridad;
                string tipo;
                cout << "ID Servicio: "; cin >> id;
                cin.ignore();
                cout << "Tipo de servicio: "; getline(cin, tipo);
                cout << "Prioridad (1=Alta, 2=Media, 3=Baja): "; cin >> prioridad;
                encolarServicio(id, tipo, prioridad);
                break;
            }
            case 4: mostrarServicios(); break;
            case 5: ejecutarServicio(); break;
            case 6: {
                int id;
                string nombre;
                cout << "ID Repuesto: "; cin >> id;
                cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                agregarRepuesto(id, nombre);
                break;
            }
            case 7: mostrarRepuestos(); break;
            case 8: usarRepuesto(); break;
            case 9: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion no valida. Intente nuevamente.\n"; break;
        }

        if (opcion != 9) {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }

    } while (opcion != 9); // Repite hasta elegir salir

    return 0;
}
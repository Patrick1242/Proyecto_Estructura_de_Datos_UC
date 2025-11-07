#include <iostream>
#include <string>
#include <cstddef>
#include <sstream>
using namespace std;

int contadorServicios = 1;
int contadorRepuestos = 1;

// === ESTRUCTURA CLIENTE ===
struct Cliente {
    int id;
    string nombre;
    string contacto;
    Cliente* siguiente;
};
Cliente* cabezaClientes = NULL;

// === REGISTRAR CLIENTE ===
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

// === MOSTRAR CLIENTES ===
void mostrarClientes() {
    if (cabezaClientes == NULL) {
        cout << "No hay clientes registrados.\n";
        return;
    }
    cout << "\n--- Lista de Clientes ---\n";
    Cliente* temp = cabezaClientes;
    while (temp != NULL) {
        cout << "ID: " << temp->id
             << " | Nombre: " << temp->nombre
             << " | Contacto: " << temp->contacto << endl;
        temp = temp->siguiente;
    }
}

// === ESTRUCTURA SERVICIO (Cola con prioridad) ===
struct Servicio {
    int id;
    string tipo;
    int prioridad;
    Servicio* siguiente;
};
Servicio* frenteServicios = NULL;

// === ENCOLAR SERVICIO ===
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

// === EJECUTAR SERVICIO ===
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

// === MOSTRAR SERVICIOS ===
void mostrarServicios() {
    if (frenteServicios == NULL) {
        cout << "No hay servicios en cola.\n";
        return;
    }
    cout << "\n--- Cola de Servicios (Postventa) ---\n";
    Servicio* temp = frenteServicios;
    while (temp != NULL) {
        cout << "ID: " << temp->id
             << " | Tipo: " << temp->tipo
             << " | Prioridad: " << temp->prioridad << endl;
        temp = temp->siguiente;
    }
}

// === ESTRUCTURA REPUESTO (Pila LIFO) ===
struct Repuesto {
    int id;
    string nombre;
    int idCliente;      
    Repuesto* abajo;
};
Repuesto* cimaRepuestos = NULL;

// === AGREGAR REPUESTO ===
void agregarRepuesto(int id, string nombre, int idCliente) {
    Repuesto* nuevo = new Repuesto{id, nombre, idCliente, cimaRepuestos};
    cimaRepuestos = nuevo;
    cout << "Repuesto agregado: " << nombre << " (Cliente ID: " << idCliente << ")" << endl;
}

// === USAR REPUESTO ===
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
void mostrarRepuestos() {
    if (cimaRepuestos == NULL) {
        cout << "Inventario vacio.\n";
        return;
    }
    cout << "\n--- Pila de Repuestos ---\n";
    Repuesto* temp = cimaRepuestos;
    while (temp != NULL) {
        cout << "ID: " << temp->id << " | Nombre: " << temp->nombre << endl;
        temp = temp->abajo;
    }
}

// === BUSCAR CLIENTE ===
bool existeCliente(int idBuscado) {
    Cliente* temp = cabezaClientes;
    while (temp != NULL) {
        if (temp->id == idBuscado) return true;
        temp = temp->siguiente;
    }
    return false;
}

string obtenerNombreCliente(int idBuscado) {
    Cliente* temp = cabezaClientes;
    while (temp != NULL) {
        if (temp->id == idBuscado) return temp->nombre;
        temp = temp->siguiente;
    }
    return "";
}

// === PROGRAMA PRINCIPAL ===
int main() {
    int opcion;

    do {

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

                // --- ID ---
                cout << "ID Cliente (ingrese manualmente): ";
                while (true) {
                    if (cin >> id && id > 0) {
                        if (!existeCliente(id)) {
                            break;
                        } else {
                            cout << "Error: El ID " << id << " ya esta registrado. Ingrese otro: ";
                        }
                    } else {
                        cout << "Error: Ingrese solo numeros mayores a 0: ";
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                }

                // --- NOMBRE (solo letras y espacios) ---
                cout << "Nombre (solo letras): ";
                while (true) {
                    getline(cin, nombre);
                    if (nombre.empty()) {
                        cout << "Error: No puede estar vacio: ";
                        continue;
                    }
                    bool valido = true;
                    for (size_t i = 0; i < nombre.length(); ++i) {
					    char c = nombre[i];
					    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
					        valido = false;
					        break;
					    }
					}
                    if (valido) break;
                    cout << "Error: Solo letras y espacios: ";
                }

                // --- CONTACTO (solo números) ---
                cout << "Contacto (solo numeros): ";
                while (true) {
                    getline(cin, contacto);
                    if (contacto.empty()) {
                        cout << "Error: No puede estar vacio: ";
                        continue;
                    }
                    bool valido = true;
                    for (size_t i = 0; i < contacto.length(); ++i) {
					    char c = contacto[i];
					    if (c < '0' || c > '9') {
					        valido = false;
					        break;
					    }
					}
                    if (valido) break;
                    cout << "Error: Solo numeros permitidos: ";
                }

                registrarCliente(id, nombre, contacto);
                break;
            }

            case 2: mostrarClientes(); break;

            case 3: {
                if (cabezaClientes == NULL) {
                    cout << "No hay clientes registrados. Registre al menos un cliente primero.\n";
                    break;
                }

                int idCliente, prioridad;
                string tipo;

                cout << "ID Cliente (registrado): ";
                while (true) {
                    if (cin >> idCliente && idCliente > 0) {
                        if (existeCliente(idCliente)) {
                            break;
                        } else {
                            cout << "Error: No existe cliente con ID " << idCliente << ". Intente otro: ";
                        }
                    } else {
                        cout << "Error: Ingrese solo numeros mayores a 0: ";
                        cin.clear();
                    }
                }

                int idServicio = contadorServicios++;
                cout << "ID Servicio (autogenerado): " << idServicio << endl;

                cout << "Tipo de servicio: ";
                getline(cin, tipo);
                cin >> tipo;
                if (tipo.empty()) tipo = "Sin descripcion";

                cout << "Prioridad (1=Alta, 2=Media, 3=Baja): ";
                while (!(cin >> prioridad) || prioridad < 1 || prioridad > 3) {
                    cout << "Error: Prioridad debe ser 1, 2 o 3: ";
                    cin.clear();
                }

                string nombreCliente = obtenerNombreCliente(idCliente);
                cout << "Servicio para: " << nombreCliente << endl;

            	encolarServicio(idServicio, tipo, prioridad);
				cout << "Servicio para cliente ID: " << idCliente << endl;
                break;
            }

            case 4: mostrarServicios(); break;
            case 5: ejecutarServicio(); break;

            case 6: {
			    if (cabezaClientes == NULL) {
			        cout << "No hay clientes registrados. Registre al menos un cliente primero.\n";
			        break;
			    }
			
			    int idCliente;
			    string nombre;
			
			    cout << "ID Cliente (registrado): ";
			    while (true) {
			        if (cin >> idCliente && idCliente > 0) {
			            if (existeCliente(idCliente)) {
			                cin.ignore(256, '\n');
			                break;
			            } else {
			                cout << "Error: No existe cliente con ID " << idCliente << ". Intente otro: ";
			            }
			        } else {
			            cout << "Error: Ingrese solo numeros mayores a 0: ";
			            cin.clear();
			            cin.ignore(256, '\n');
			        }
			    }
			
			    int idRepuesto = contadorRepuestos++;
			    cout << "ID Repuesto (autogenerado): " << idRepuesto << endl;
			
			    cout << "Nombre del repuesto: ";
			    cin.ignore(256, '\n');
			    getline(cin, nombre);
			    if (nombre.empty()) nombre = "Sin nombre";
			
			    string nombreCliente = obtenerNombreCliente(idCliente);
			    cout << "Repuesto para: " << nombreCliente << endl;
			
			    // SIN to_string(), SIN <sstream>
			    agregarRepuesto(idRepuesto, nombre, idCliente);
			    break;
			}

            case 7: mostrarRepuestos(); break;
            case 8: usarRepuesto(); break;
            case 9: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion no valida. Intente nuevamente.\n"; break;
        }

        if (opcion != 9) {
            cout << "\nPresione Enter para continuar...";
            cin.get();  // Espera Enter
        }

    } while (opcion != 9);

    // === Liberar memoria de clientes ===
    Cliente* actual = cabezaClientes;
    while (actual != NULL) {
        Cliente* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }

    return 0;
}

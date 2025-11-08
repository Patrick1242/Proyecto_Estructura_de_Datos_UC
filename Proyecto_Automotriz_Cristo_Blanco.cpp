#include <iostream>     // Necesario para cout, cin
#include <string>       // Para usar cadenas de texto (string)
#include <cstddef>      // Define NULL y size_t
#include <sstream>      // (No usado, pero a veces útil para conversiones)
using namespace std;    // Evita escribir std:: cada vez

// === CONTADORES GLOBALES ===
int contadorServicios = 1;   // Genera ID único para cada servicio
int contadorRepuestos = 1;   // Genera ID único para cada repuesto

// ==================================================
// === ESTRUCTURA CLIENTE (Lista enlazada) ===
// ==================================================
struct Cliente {
    int id;                  // ID del cliente (único, ingresado manualmente)
    string nombre;           // Nombre completo
    string contacto;         // Teléfono o correo
    Cliente* siguiente;      // Puntero al siguiente cliente (NULL = final)
};
Cliente* cabezaClientes = NULL;  // Apunta al primer cliente. NULL = lista vacía

// ==================================================
// === REGISTRAR CLIENTE ===
// ==================================================
void registrarCliente(int id, string nombre, string contacto) {
    Cliente* nuevo = new Cliente;  // Reserva memoria dinámica para nuevo cliente
    nuevo->id = id;                // Asigna el ID recibido
    nuevo->nombre = nombre;        // Asigna nombre
    nuevo->contacto = contacto;    // Asigna contacto
    nuevo->siguiente = NULL;       // Este será el último (por ahora)

    if (cabezaClientes == NULL) {  // Si es el primer cliente
        cabezaClientes = nuevo;    // La cabeza ahora es este nodo
    } else {
        Cliente* temp = cabezaClientes;  // Comienza desde el primer cliente
        while (temp->siguiente != NULL) { // Recorre hasta el último nodo
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;  // Engancha el nuevo nodo al final
    }
    cout << "Cliente registrado: " << nombre << endl;  // Confirma registro
}

// ==================================================
// === MOSTRAR TODOS LOS CLIENTES ===
// ==================================================
void mostrarClientes() {
    if (cabezaClientes == NULL) {  // Verifica si la lista está vacía
        cout << "No hay clientes registrados.\n";
        return;  // Sale de la función
    }
    cout << "\n--- Lista de Clientes ---\n";
    Cliente* temp = cabezaClientes;  // Puntero para recorrer la lista
    while (temp != NULL) {           // Mientras no llegue al final
        cout << "ID: " << temp->id
             << " | Nombre: " << temp->nombre
             << " | Contacto: " << temp->contacto << endl;
        temp = temp->siguiente;      // Avanza al siguiente nodo
    }
}

// ==================================================
// === ESTRUCTURA SERVICIO (Cola con prioridad) ===
// ==================================================
struct Servicio {
    int id;           // ID único del servicio
    string tipo;      // Descripción del servicio
    int prioridad;    // 1 = Alta, 2 = Media, 3 = Baja (menor número = más urgente)
    Servicio* siguiente; // Puntero al siguiente servicio
};
Servicio* frenteServicios = NULL;  // Apunta al primer servicio (el de mayor prioridad)

// ==================================================
// === AGREGAR SERVICIO (encolar con prioridad) ===
// ==================================================
void encolarServicio(int id, string tipo, int prioridad) {
    Servicio* nuevo = new Servicio;  // Crea nuevo nodo
    nuevo->id = id;
    nuevo->tipo = tipo;
    nuevo->prioridad = prioridad;
    nuevo->siguiente = NULL;

    // Caso 1: Cola vacía o nuevo tiene mayor prioridad
    if (frenteServicios == NULL || prioridad < frenteServicios->prioridad) {
        nuevo->siguiente = frenteServicios;  // El actual frente queda detrás
        frenteServicios = nuevo;             // Nuevo se convierte en el frente
    } else {
        Servicio* temp = frenteServicios;
        // Busca la posición correcta (orden ascendente por prioridad)
        while (temp->siguiente != NULL && temp->siguiente->prioridad <= prioridad) {
            temp = temp->siguiente;
        }
        nuevo->siguiente = temp->siguiente;  // Inserta después de temp
        temp->siguiente = nuevo;
    }
    cout << "Servicio agregado: " << tipo << " (Prioridad " << prioridad << ")\n";
}

// ==================================================
// === EJECUTAR SERVICIO (desencolar) ===
// ==================================================
void ejecutarServicio() {
    if (frenteServicios == NULL) {  // Verifica si hay servicios
        cout << "No hay servicios pendientes.\n";
        return;
    }
    Servicio* temp = frenteServicios;       // Toma el servicio de mayor prioridad
    frenteServicios = frenteServicios->siguiente; // Avanza el frente
    cout << "Ejecutando servicio ID " << temp->id << ": " << temp->tipo << endl;
    delete temp;  // Libera memoria del nodo eliminado
}

// ==================================================
// === MOSTRAR COLA DE SERVICIOS ===
// ==================================================
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

// ==================================================
// === ESTRUCTURA REPUESTO (Pila LIFO) ===
// ==================================================
struct Repuesto {
    int id;           // ID único del repuesto
    string nombre;    // Nombre del repuesto
    int idCliente;    // Cliente asociado
    Repuesto* abajo;  // Puntero al repuesto anterior (debajo en la pila)
};
Repuesto* cimaRepuestos = NULL;  // Apunta al último repuesto agregado (cima)

// ==================================================
// === AGREGAR REPUESTO (push) ===
// ==================================================
void agregarRepuesto(int id, string nombre, int idCliente) {
    Repuesto* nuevo = new Repuesto;
    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->idCliente = idCliente;
    nuevo->abajo = cimaRepuestos;  // El anterior queda debajo
    cimaRepuestos = nuevo;         // Nuevo es la nueva cima
    cout << "Repuesto agregado: " << nombre << " (Cliente ID: " << idCliente << ")" << endl;
}

// ==================================================
// === USAR REPUESTO (pop) ===
// ==================================================
void usarRepuesto() {
    if (cimaRepuestos == NULL) {
        cout << "No hay repuestos disponibles.\n";
        return;
    }
    Repuesto* temp = cimaRepuestos;         // Toma el repuesto de arriba
    cimaRepuestos = cimaRepuestos->abajo;   // Baja la pila
    cout << "Usando repuesto: " << temp->nombre << endl;
    delete temp;  // Libera memoria
}

// ==================================================
// === MOSTRAR PILA DE REPUESTOS ===
// ==================================================
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

// ==================================================
// === BUSCAR CLIENTE (devuelve bool) ===
// ==================================================
bool existeCliente(int idBuscado) {
    Cliente* temp = cabezaClientes;
    while (temp != NULL) {
        if (temp->id == idBuscado) return true;  // Encontrado → retorna true
        temp = temp->siguiente;
    }
    return false;  // No encontrado → retorna false
}

string obtenerNombreCliente(int idBuscado) {
    Cliente* temp = cabezaClientes;
    while (temp != NULL) {
        if (temp->id == idBuscado) return temp->nombre;
        temp = temp->siguiente;
    }
    return "";  // No encontrado
}

// ==================================================
// === PROGRAMA PRINCIPAL ===
// ==================================================
int main() {
    int opcion;
    do {
        // --- MENÚ PRINCIPAL ---
        cout << "==================================================\n";
        cout << "|| SISTEMA DE GESTION AUTOMOTRIZ ||\n";
        cout << "==================================================\n";
        cout << "|| 1. Registrar cliente (Ventas) ||\n";
        cout << "|| 2. Mostrar clientes ||\n";
        cout << "|| 3. Agregar servicio (Postventa) ||\n";
        cout << "|| 4. Mostrar servicios ||\n";
        cout << "|| 5. Ejecutar servicio ||\n";
        cout << "|| 6. Agregar repuesto (Servicio Tecnico) ||\n";
        cout << "|| 7. Mostrar repuestos ||\n";
        cout << "|| 8. Usar repuesto ||\n";
        cout << "|| 9. Salir ||\n";
        cout << "==================================================\n";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
            case 1: {
                int id;
                string nombre, contacto;

                // === VALIDACIÓN DE ID (único y positivo) ===
                cout << "ID Cliente (ingrese manualmente): ";
                while (true) {
                    if (cin >> id && id > 0) {  // Entrada es número y mayor a 0
                        if (!existeCliente(id)) {  // Llama a función bool: ¿existe?
                            cin.ignore(256, '\n'); // Limpia salto de línea
                            break;
                        } else {
                            cout << "Error: El ID " << id << " ya esta registrado. Ingrese otro: ";
                        }
                    } else {
                        cout << "Error: Ingrese solo numeros mayores a 0: ";
                        cin.clear();           // Limpia error de cin
                        cin.ignore(256, '\n'); // Descarta entrada inválida
                    }
                }

                // === VALIDACIÓN DE NOMBRE (solo letras y espacios) ===
                cout << "Nombre (solo letras): ";
                while (true) {
                    getline(cin, nombre);  // Lee línea completa
                    if (nombre.empty()) {  // Verifica si está vacío
                        cout << "Error: No puede estar vacio: ";
                        continue;
                    }
                    bool valido = true;    // Bandera para saber si es válido
                    for (size_t i = 0; i < nombre.length(); ++i) {
                        char c = nombre[i];
                        // Verifica si es letra o espacio
                        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ')) {
                            valido = false;  // Marca como inválido
                            break;
                        }
                    }
                    if (valido) break;  // Si todo bien, sale del bucle
                    cout << "Error: Solo letras y espacios: ";
                }

                // === VALIDACIÓN DE CONTACTO (solo números) ===
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
                        if (c < '0' || c > '9') {  // Si no es dígito
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

                // === VALIDAR ID CLIENTE EXISTENTE ===
                cout << "ID Cliente (registrado): ";
                while (true) {
                    if (cin >> idCliente && idCliente > 0) {
                        if (existeCliente(idCliente)) {  // Usa bool para verificar
                            break;
                        } else {
                            cout << "Error: No existe cliente con ID " << idCliente << ". Intente otro: ";
                        }
                    } else {
                        cout << "Error: Ingrese solo numeros mayores a 0: ";
                        cin.clear();
                    }
                }

                int idServicio = contadorServicios++;  // ID automático
                cout << "ID Servicio (autogenerado): " << idServicio << endl;

                cout << "Tipo de servicio: ";
                cin.ignore();  // Limpia salto de línea pendiente
                getline(cin, tipo);
                if (tipo.empty()) tipo = "Sin descripcion";

                // === VALIDAR PRIORIDAD (1, 2 o 3) ===
                cout << "Prioridad (1=Alta, 2=Media, 3=Baja): ";
                while (!(cin >> prioridad) || prioridad < 1 || prioridad > 3) {
                    cout << "Error: Prioridad debe ser 1, 2 o 3: ";
                    cin.clear();           // Limpia error
                    cin.ignore(256, '\n'); // Descarta entrada inválida
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

                // === VALIDAR ID CLIENTE PARA REPUESTO ===
                cout << "ID Cliente (registrado): ";
                while (true) {
                    if (cin >> idCliente && idCliente > 0) {
                        if (existeCliente(idCliente)) {  // Usa función bool
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

                int idRepuesto = contadorRepuestos++;  // ID automático
                cout << "ID Repuesto (autogenerado): " << idRepuesto << endl;

                cout << "Nombre del repuesto: ";
                cin.ignore();  // Limpia buffer
                getline(cin, nombre);
                if (nombre.empty()) nombre = "Sin nombre";

                string nombreCliente = obtenerNombreCliente(idCliente);
                cout << "Repuesto para: " << nombreCliente << endl;
                agregarRepuesto(idRepuesto, nombre, idCliente);
                break;
            }

            case 7: mostrarRepuestos(); break;
            case 8: usarRepuesto(); break;
            case 9: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion no valida. Intente nuevamente.\n"; break;
        }

        // === PAUSA HASTA ENTER===
        if (opcion != 9) {
            cout << "\nPresione Enter para continuar...";
            cin.get();  // Espera una tecla (Enter)
        }
    } while (opcion != 9);  // Repite hasta elegir 9

    // ==================================================
    // === LIBERAR MEMORIA DE CLIENTES ===
    // ==================================================
    Cliente* actual = cabezaClientes;
    while (actual != NULL) {
        Cliente* siguiente = actual->siguiente;  // Guarda el siguiente
        delete actual;                           // Borra el nodo actual
        actual = siguiente;                      // Avanza
    }

    return 0; 
}
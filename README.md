# Sistema de Gestión Automotriz  
- **Versión 1.0** – *C++ Consola*
- **Desarrolladores:**
- Lima Tintaya Jeferson Jose
- Leguia Choquemamani Patrick Antonio


---

## Descripción General
Programa en **C++** para la gestión integral de un **taller automotriz**, estructurado en tres módulos funcionales:

| Módulo | Estructura de Datos | Descripción |
|--------|---------------------|-----------|
| **Ventas** | Lista enlazada simple | Registro y visualización de clientes |
| **Postventa** | Cola con prioridad | Gestión de servicios pendientes (1=Alta, 2=Media, 3=Baja) |
| **Servicio Técnico** | Pila (LIFO) | Inventario de repuestos |

---

## Características Clave
- **ID Cliente**: Ingresado manualmente, validado contra duplicados  
- **ID Servicio / Repuesto**: Generado automáticamente (`contador++`)  
- **Validaciones de entrada**:  
  - `ID` y `contacto`: solo dígitos  
  - `Nombre`: solo letras y espacios  
  - `Prioridad`: solo 1, 2 o 3  
- **Liberación completa de memoria** al cerrar  
- **Interfaz en consola con menú en caja**  
- **Pausa con `Enter` entre operaciones**  

---

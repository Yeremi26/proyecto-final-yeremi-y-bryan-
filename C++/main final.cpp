#include <iostream>
#include <string>
#include <list>
#include <algorithm>

// Estructura para un producto
// Representa los atributos b�sicos de un producto en el inventario.
struct Producto {
    std::string nombre; // Nombre del producto.
    double precio;      // Precio del producto.
    int cantidad;       // Cantidad disponible en inventario.
};

// Estructura para una solicitud de compra
// Almacena informaci�n sobre una solicitud registrada por alg�n cliente.
struct Solicitud {
    int id;             // Identificador �nico de la solicitud.
    std::string descripcion; // Descripci�n de la solicitud.
};

// Estructura para un cliente
// Representa a un cliente que est� en espera.
struct Cliente {
    int id;             // Identificador �nico del cliente.
    std::string nombre; // Nombre del cliente.
};

// Historial de cambios en el inventario
// Permite llevar un registro de los cambios realizados, �til para deshacer acciones.
struct Cambio {
    std::string tipo;   // Tipo de cambio: "agregar" o "eliminar".
    Producto producto;  // Producto afectado por el cambio.
};

// Clase para la gesti�n del sistema
// Contiene listas para manejar inventario, solicitudes, clientes en espera, y el historial de cambios.
class SistemaGestion {
private:
    // Listas que almacenan la informaci�n principal del sistema.
    std::list<Producto> inventario;        // Almacena los productos registrados.
    std::list<Solicitud> solicitudes;     // Almacena las solicitudes pendientes.
    std::list<Cliente> clientesEnEspera;  // Lista de clientes en espera.
    std::list<Cambio> historialCambios;   // Registro de los cambios realizados en el inventario.

public:
    // M�todos para la gesti�n de inventario
    void registrarProducto(const Producto& producto);
    void eliminarProducto(const std::string& nombreProducto);
    void consultarProducto(const std::string& nombreProducto);
    void listarProductos();

    // M�todos para la gesti�n de solicitudes
    void registrarSolicitud(const Solicitud& solicitud);
    void procesarSolicitud();
    void consultarSolicitudEnProceso();
    void listarSolicitudesPendientes();

    // M�todos para la gesti�n de clientes en espera
    void registrarClienteEnEspera(const Cliente& cliente);
    void atenderCliente();
    void consultarListaDeEspera();

    // M�todos para la gesti�n del historial de cambios
    void deshacerUltimaAccion();
};

// Implementaci�n de los m�todos del SistemaGestion

// M�todo para agregar un producto al inventario.
void SistemaGestion::registrarProducto(const Producto& producto) {
    inventario.push_back(producto); // Agrega el producto al final de la lista.
    historialCambios.push_back({"agregar", producto}); // Registra el cambio en el historial.
    std::cout << "Producto agregado: " << producto.nombre << std::endl;
}

// M�todo para eliminar un producto del inventario.
void SistemaGestion::eliminarProducto(const std::string& nombreProducto) {
    // Busca el producto por su nombre usando std::find_if.
    auto it = std::find_if(inventario.begin(), inventario.end(), [&](const Producto& p) {
        return p.nombre == nombreProducto;
    });

    if (it != inventario.end()) {
        // Si el producto existe, registra el cambio y lo elimina.
        historialCambios.push_back({"eliminar", *it});
        inventario.erase(it);
        std::cout << "Producto eliminado: " << nombreProducto << std::endl;
    } else {
        std::cout << "Producto no encontrado." << std::endl;
    }
}

// M�todo para consultar informaci�n de un producto espec�fico.
void SistemaGestion::consultarProducto(const std::string& nombreProducto) {
    // Busca el producto por su nombre.
    auto it = std::find_if(inventario.begin(), inventario.end(), [&](const Producto& p) {
        return p.nombre == nombreProducto;
    });

    if (it != inventario.end()) {
        // Si se encuentra, muestra su informaci�n.
        std::cout << "Producto: " << it->nombre << ", Precio: " << it->precio << ", Cantidad: " << it->cantidad << std::endl;
    } else {
        std::cout << "Producto no encontrado." << std::endl;
    }
}

// M�todo para listar todos los productos en el inventario.
void SistemaGestion::listarProductos() {
    // Ordena los productos por nombre antes de mostrarlos.
    inventario.sort([](const Producto& a, const Producto& b) {
        return a.nombre < b.nombre;
    });

    for (const auto& producto : inventario) {
        // Muestra cada producto en el inventario.
        std::cout << "Producto: " << producto.nombre << ", Precio: " << producto.precio << ", Cantidad: " << producto.cantidad << std::endl;
    }
}

// M�todo para registrar una nueva solicitud.
void SistemaGestion::registrarSolicitud(const Solicitud& solicitud) {
    solicitudes.push_back(solicitud); // Agrega la solicitud al final de la lista.
    std::cout << "Solicitud registrada: " << solicitud.descripcion << std::endl;
}

// M�todo para procesar la primera solicitud en la lista.
void SistemaGestion::procesarSolicitud() {
    if (!solicitudes.empty()) {
        auto solicitud = solicitudes.front(); // Obtiene la primera solicitud.
        solicitudes.pop_front(); // La elimina de la lista.
        std::cout << "Procesando solicitud: " << solicitud.descripcion << std::endl;
    } else {
        std::cout << "No hay solicitudes pendientes." << std::endl;
    }
}

// M�todo para consultar la solicitud en proceso (la primera de la lista).
void SistemaGestion::consultarSolicitudEnProceso() {
    if (!solicitudes.empty()) {
        auto solicitud = solicitudes.front();
        std::cout << "Solicitud en proceso: " << solicitud.descripcion << std::endl;
    } else {
        std::cout << "No hay solicitudes en proceso." << std::endl;
    }
}

// M�todo para listar todas las solicitudes pendientes.
void SistemaGestion::listarSolicitudesPendientes() {
    for (const auto& solicitud : solicitudes) {
        std::cout << "Solicitud pendiente: " << solicitud.descripcion << std::endl;
    }
}

// M�todo para registrar un cliente en espera.
void SistemaGestion::registrarClienteEnEspera(const Cliente& cliente) {
    clientesEnEspera.push_back(cliente); // Agrega el cliente al final de la lista.
    std::cout << "Cliente registrado: " << cliente.nombre << std::endl;
}

// M�todo para atender al primer cliente en espera.
void SistemaGestion::atenderCliente() {
    if (!clientesEnEspera.empty()) {
        auto cliente = clientesEnEspera.front(); // Obtiene el primer cliente.
        clientesEnEspera.pop_front(); // Lo elimina de la lista.
        std::cout << "Atendiendo cliente: " << cliente.nombre << std::endl;
    } else {
        std::cout << "No hay clientes en espera." << std::endl;
    }
}

// M�todo para consultar todos los clientes en espera.
void SistemaGestion::consultarListaDeEspera() {
    for (const auto& cliente : clientesEnEspera) {
        std::cout << "Cliente en espera: " << cliente.nombre << std::endl;
    }
}

// M�todo para deshacer la �ltima acci�n registrada en el historial.
void SistemaGestion::deshacerUltimaAccion() {
    if (!historialCambios.empty()) {
        auto cambio = historialCambios.back();
        historialCambios.pop_back(); // Elimina el �ltimo cambio del historial.

        if (cambio.tipo == "agregar") {
            // Si fue un agregado, elimina el producto del inventario.
            auto it = std::find_if(inventario.begin(), inventario.end(), [&](const Producto& p) {
                return p.nombre == cambio.producto.nombre;
            });
            if (it != inventario.end()) {
                inventario.erase(it);
                std::cout << "Deshacer: Producto agregado eliminado: " << cambio.producto.nombre << std::endl;
            }
        } else if (cambio.tipo == "eliminar") {
            // Si fue una eliminaci�n, restaura el producto en el inventario.
            inventario.push_back(cambio.producto);
            std::cout << "Deshacer: Producto eliminado restaurado: " << cambio.producto.nombre << std::endl;
        }
    } else {
        std::cout << "No hay cambios para deshacer." << std::endl;
    }
}

// Funci�n principal con men� interactivo.
int main() {
    SistemaGestion sistema; // Instancia del sistema de gesti�n.
    int opcion;

    do {
        // Mostrar el men� al usuario.
        std::cout << "\n---- Men� del Sistema de Gesti�n ----\n";
        std::cout << "1. Registrar Producto\n";
        std::cout << "2. Eliminar Producto\n";
        std::cout << "3. Consultar Producto\n";
        std::cout << "4. Listar Productos\n";
        std::cout << "5. Registrar Solicitud\n";
        std::cout << "6. Procesar Solicitud\n";
        std::cout << "7. Consultar Solicitud en Proceso\n";
        std::cout << "8. Listar Solicitudes Pendientes\n";
        std::cout << "9. Registrar Cliente en Espera\n";
        std::cout << "10. Atender Cliente\n";
        std::cout << "11. Consultar Lista de Espera\n";
        std::cout << "12. Deshacer �ltima Acci�n\n";
        std::cout << "13. Salir\n";
        std::cout << "Seleccione una opci�n: ";
        
        std::cin >> opcion; // Lee la opci�n seleccionada por el usuario.

        // Ejecuta la acci�n correspondiente seg�n la opci�n seleccionada.
        switch (opcion) {
            case 1: {
                Producto producto;
                std::cout << "Ingrese nombre del producto: ";
                std::cin >> producto.nombre;
                std::cout << "Ingrese precio del producto: ";
                std::cin >> producto.precio;
                std::cout << "Ingrese cantidad del producto: ";
                std::cin >> producto.cantidad;
                sistema.registrarProducto(producto);
                break;
            }
            case 2: {
                std::string nombre;
                std::cout << "Ingrese nombre del producto a eliminar: ";
                std::cin >> nombre;
                sistema.eliminarProducto(nombre);
                break;
            }
            case 3: {
                std::string nombre;
                std::cout << "Ingrese nombre del producto a consultar: ";
                std::cin >> nombre;
                sistema.consultarProducto(nombre);
                break;
            }
            case 4:
                sistema.listarProductos();
                break;
            case 5: {
                Solicitud solicitud;
                std::cout << "Ingrese descripci�n de la solicitud: ";
                std::cin.ignore(); // Limpia el buffer de entrada.
                std::getline(std::cin, solicitud.descripcion);
                sistema.registrarSolicitud(solicitud);
                break;
            }
            case 6:
                sistema.procesarSolicitud();
                break;
            case 7:
                sistema.consultarSolicitudEnProceso();
                break;
            case 8:
                sistema.listarSolicitudesPendientes();
                break;
            case 9: {
                Cliente cliente;
                std::cout << "Ingrese nombre del cliente en espera: ";
                std::cin >> cliente.nombre;
                sistema.registrarClienteEnEspera(cliente);
                break;
            }
            case 10:
                sistema.atenderCliente();
                break;
            case 11:
                sistema.consultarListaDeEspera();
                break;
            case 12:
                sistema.deshacerUltimaAccion();
                break;
            case 13:
                std::cout << "Saliendo del sistema...\n";
                break;
            default:
                std::cout << "Opci�n no v�lida.\n";
        }
    } while (opcion != 13); // El men� sigue apareciendo hasta que el usuario elija salir.

    return 0;
}


#include <iostream>
#include <string>
#include "Estudiante.h"

using namespace std;

int main() {
    // Variables para capturar datos
    string codigo, nombres, apellidos, direccion, fecha_nacimiento;
    int telefono = 0, id_tipo_sangre = 0, id_estudiante = 0;
    int opcion = 0;

    // Instancia de la clase
    Estudiante e = Estudiante();

    do {
        system("cls"); // Limpia la pantalla en cada iteración del menú
        cout << "============== SISTEMA DE REGISTRO UMG ==============" << endl;
        cout << "1. Registrar Estudiante (Crear)" << endl;
        cout << "2. Ver Listado de Estudiantes (Leer)" << endl;
        cout << "3. Modificar Datos de Estudiante (Actualizar)" << endl;
        cout << "4. Eliminar Estudiante (Borrar)" << endl;
        cout << "5. Salir" << endl;
        cout << "====================================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpia el buffer para evitar problemas con getline

        switch (opcion) {
        case 1:
            cout << "\n--- NUEVO REGISTRO ---" << endl;
            cout << "Ingrese Codigo: "; cin >> codigo; cin.ignore();
            cout << "Ingrese Nombres: "; getline(cin, nombres);
            cout << "Ingrese Apellidos: "; getline(cin, apellidos);
            cout << "Ingrese Direccion: "; getline(cin, direccion);
            cout << "Ingrese Telefono: "; cin >> telefono; cin.ignore();
            cout << "Ingrese Fecha Nacimiento (YYYY-MM-DD): "; getline(cin, fecha_nacimiento);
            cout << "Ingrese ID Tipo Sangre: "; cin >> id_tipo_sangre;

            // Seteamos los datos al objeto
            e = Estudiante(nombres, apellidos, direccion, telefono, fecha_nacimiento, id_tipo_sangre, codigo, 0);

            // Aquí se ejecuta la validacion de existencia y el insert
            e.crear();

            cout << "\nPresione Enter para continuar...";
            cin.ignore(); cin.get();
            break;

        case 2:
            cout << "\n--- LISTADO ACTUAL EN BASE DE DATOS ---" << endl;
            e.leer();
            cout << "\nPresione Enter para continuar...";
            cin.get();
            break;

        case 3:
            e.leer(); // Mostramos la lista para que el usuario sepa qué ID elegir
            cout << "\nIngrese el ID del estudiante a MODIFICAR: ";
            cin >> id_estudiante;
            cout << "Ingrese Nuevo Codigo: "; cin >> codigo; cin.ignore();
            cout << "Ingrese Nuevos Nombres: "; getline(cin, nombres);
            cout << "Ingrese Nuevos Apellidos: "; getline(cin, apellidos);
            cout << "Ingrese Nueva Direccion: "; getline(cin, direccion);
            cout << "Ingrese Nuevo Telefono: "; cin >> telefono; cin.ignore();
            cout << "Ingrese Nueva Fecha Nacimiento: "; getline(cin, fecha_nacimiento);
            cout << "Ingrese Nuevo ID Tipo Sangre: "; cin >> id_tipo_sangre;

            // Actualizamos los atributos del objeto antes de llamar al metodo
            e.setId_estudiante(id_estudiante);
            e.setCodigo(codigo);
            e.setNombres(nombres);
            e.setApellidos(apellidos);
            e.setDireccion(direccion);
            e.setTelefono(telefono);
            e.setFecha_Nacimiento(fecha_nacimiento);
            e.setId_Tipo_Sangre(id_tipo_sangre);

            e.actualizar();

            cout << "\nPresione Enter para continuar...";
            cin.ignore(); cin.get();
            break;

        case 4:
            e.leer();
            cout << "\nIngrese el ID del estudiante a ELIMINAR: ";
            cin >> id_estudiante;

            e.setId_estudiante(id_estudiante);
            e.borrar();

            cout << "\nPresione Enter para continuar...";
            cin.ignore(); cin.get();
            break;

        case 5:
            cout << "Saliendo del sistema..." << endl;
            break;

        default:
            cout << "Opcion no valida, intente de nuevo." << endl;
            system("pause");
            break;
        }

    } while (opcion != 5);

    return 0;
}

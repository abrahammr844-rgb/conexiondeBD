#pragma once
#include <iostream>
#include "ConexionBD.h"
#include "Persona.h"
#include <mysql.h>
#include <string>

using namespace std;

class Estudiante : public Persona {
    // Atributos
private:
    string codigo;
    int id_estudiante = 0;

    // Constructor
public:
    Estudiante() {}
    Estudiante(string nom, string ape, string dir, int tel, string fn, int id_ts, string cod, int id_e)
        : Persona(nom, ape, dir, tel, fn, id_ts) {
        codigo = cod;
        id_estudiante = id_e;
    }

    // Metodos get y set
    void setId_estudiante(int e) { id_estudiante = e; }
    void setCodigo(string c) { codigo = c; }
    void setNombres(string n) { nombres = n; }
    void setApellidos(string a) { apellidos = a; }
    void setDireccion(string d) { direccion = d; }
    void setTelefono(int t) { telefono = t; }
    void setFecha_Nacimiento(string f) { fecha_nacimiento = f; }
    void setId_Tipo_Sangre(int ts) { id_tipo_sangre = ts; }

    int getId_estudiante() { return id_estudiante; }
    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getDireccion() { return direccion; }
    int getTelefono() { return telefono; }
    string getFecha_nacimiento() { return fecha_nacimiento; }
    int getId_tipo_sangre() { return id_tipo_sangre; }

    // --- VALIDACIÓN DE EXISTENCIA ---
    bool existeCodigo(string cod) {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        bool existe = false;
        if (cn.getConector()) {
            string consulta = "SELECT codigo FROM estudiantes WHERE codigo = '" + cod + "'";
            mysql_query(cn.getConector(), consulta.c_str());
            MYSQL_RES* res = mysql_store_result(cn.getConector());
            if (res && mysql_num_rows(res) > 0) {
                existe = true;
            }
            mysql_free_result(res);
        }
        cn.cerrar_conexion();
        return existe;
    }

    // --- MÉTODOS CRUD CON VALIDACIONES --- CREADO POR MI JEJE 

    void crear() {
        // Validación lógica: evitar duplicados
        if (existeCodigo(codigo)) {
            cout << "\nxxxx Error: El codigo [" << codigo << "] ya existe. Registro cancelado. xxxx" << endl;
            return;
        }

        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConector()) {
            string t = to_string(telefono);
            string id_ts = to_string(id_tipo_sangre);
            string consulta = "INSERT INTO estudiantes(codigo,nombres,apellidos,direccion,telefono,fecha_nacimiento,id_tipo_sangre) VALUES ('" + codigo + "','" + nombres + "','" + apellidos + "','" + direccion + "'," + t + ",'" + fecha_nacimiento + "'," + id_ts + ");";

            if (!mysql_query(cn.getConector(), consulta.c_str())) {
                cout << ">>>> Ingreso de Datos Exitoso <<<<" << endl;
            }
            else {
                // Validación técnica: error de MySQL
                cout << "xxxx Error al insertar: " << mysql_error(cn.getConector()) << " xxxx" << endl;
            }
        }
        else {
            cout << " xxxx Fallo la Conexion con la BD xxxx " << endl;
        }
        cn.cerrar_conexion();
    }

    void leer() {
        ConexionBD cn = ConexionBD();
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConector()) {
            cout << "___________ Datos del Estudiante ___________" << endl;
            string consulta = "SELECT e.id_estudiante, e.codigo, e.nombres, e.apellidos, e.direccion, e.telefono, e.fecha_nacimiento, ts.sangre FROM estudiantes as e INNER JOIN tipos_sangre as ts ON e.id_tipo_sangre = ts.id_tipo_sangre;";

            if (!mysql_query(cn.getConector(), consulta.c_str())) {
                resultado = mysql_store_result(cn.getConector());
                while (fila = mysql_fetch_row(resultado)) {
                    cout << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << " | " << fila[5] << " | " << fila[6] << " | " << fila[7] << endl;
                }
                mysql_free_result(resultado);
            }
            else {
                cout << "xxxx Error en lectura: " << mysql_error(cn.getConector()) << " xxxx" << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void actualizar() {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConector()) {
            string t = to_string(telefono);
            string id_ts = to_string(id_tipo_sangre);
            string id_e = to_string(id_estudiante);
            string consulta = "UPDATE estudiantes SET codigo = '" + codigo + "', nombres = '" + nombres + "', apellidos='" + apellidos + "', direccion='" + direccion + "', telefono=" + t + ", fecha_nacimiento = '" + fecha_nacimiento + "', id_tipo_sangre=" + id_ts + " WHERE id_estudiante = " + id_e;

            if (!mysql_query(cn.getConector(), consulta.c_str())) {
                cout << ">>>> Modificacion Exitosa <<<<" << endl;
            }
            else {
                cout << "xxxx Error al actualizar: " << mysql_error(cn.getConector()) << " xxxx" << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void borrar() {
        ConexionBD cn = ConexionBD();
        cn.abrir_conexion();
        if (cn.getConector()) {
            string id_e = to_string(id_estudiante);
            string consulta = "DELETE FROM estudiantes WHERE id_estudiante = " + id_e;

            if (!mysql_query(cn.getConector(), consulta.c_str())) {
                cout << ">>>> Registro Eliminado Exitosamente <<<<" << endl;
            }
            else {
                cout << "xxxx Error al eliminar: " << mysql_error(cn.getConector()) << " xxxx" << endl;
            }
        }
        cn.cerrar_conexion();
    }
};

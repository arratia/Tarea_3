/* 
 * File:   main.cpp
 * Author: Cristobal
 *
 * Created on 11 de abril de 2013, 3:14
 */

#include <cstdlib>
#include <iostream>
#include <libpq-fe.h>


using namespace std;

PGconn *cnn = NULL;
PGresult *result = NULL;

int main(int argc, char** argv) {

    int i;

    cnn = PQsetdbLogin("sebastian.cl","5432",NULL,NULL,"iswdb","isw","isw"); // Se crea la conexión con los datos de nuestro servidor

    if (PQstatus(cnn) != CONNECTION_BAD) {
        cout << "Estamos conectados a PostgreSQL!" << endl;
        result = PQexec(cnn, "SELECT * FROM cursos");

        if (result != NULL) {
            int tuplas = PQntuples(result);
            int campos = PQnfields(result);
            cout << "No. Filas:" << tuplas << endl;
            cout << "No. Campos:" << campos << endl;

            cout << "Los nombres de los campos son:" << endl;

            for (i=0; i<campos; i++) {
                cout << PQfname(result,i) << " | ";
            }

            cout << endl << "Contenido de la tabla" << endl;

            for (i=0; i<tuplas; i++) {
                for (int j=0; j<campos; j++) {
                    cout << PQgetvalue(result,i,j) << " | ";
                }
                cout << endl;
            }
        }

       // Ahora nos toca liberar la memoria
        PQclear(result);

    } else {
        cout << "Error de conexion" << endl;
    
  }

    PQfinish(cnn);
}


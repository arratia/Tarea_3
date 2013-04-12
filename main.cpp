/* 
 * AutorES: Cristobal Perez
+ *         Nicolas Arratia
+ *         Josimar Gonzalez
 */

#include <cstdlib>
#include <iostream>
#include <libpq-fe.h> //libreria para realizar conexion con la base de datos postgresql


using namespace std;

PGconn *cnn = NULL;
PGresult *result = NULL;

int main(int argc, char** argv) 
{

    int i;

    cnn = PQsetdbLogin("sebastian.cl","5432",NULL,NULL,"iswdb","isw","isw"); // Se crea la conexión con los datos de nuestro servidor

    if (PQstatus(cnn) != CONNECTION_BAD) {
        cout << "Estamos conectados a PostgreSQL!" << endl;
        result = PQexec(cnn, "SELECT docente_id as \"cod docente\", AVG(nota) as \"promedio de notas\", STDDEV(nota) as \"desviacion estandar de notas\"  FROM cursos AS c, asignaturas_cursadas AS a WHERE c.curso_id = a.curso_id GROUP BY docente_id");
//);
        if (result != NULL) {
            int tuplas = PQntuples(result);
            int campos = PQnfields(result);
            cout << "No. Filas:" << tuplas << endl;
            cout << "No. Columnas:" << campos << endl;

            cout << "NOMBRES DE LAS COLUMNAS:" << endl;
 	    cout << "***************************************" << endl;

            for (i=0; i<campos; i++) {
                cout << PQfname(result,i) << " | ";
            }

            cout << endl << "*******************************" << endl;

            for (i=0; i<tuplas; i++) {
                for (int j=0; j<campos; j++) {
                    cout << PQgetvalue(result,i,j) << " | ";
                }
                cout << endl;
            }
        }

       
        PQclear(result); // Ahora nos toca liberar la memoria

    } else {
        cout << "Error de conexion" << endl;
    
  }

    PQfinish(cnn);
}

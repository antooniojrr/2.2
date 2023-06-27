// Ejecución: ./generador <archivo.dat> <num_vacas>
/*
    @name generador.cpp
    @author Antonio Rodríguez, David Kessler, Santiago López
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

/*
    @brief Función para generar datos de tipo double aleatorios en un intervalo [fMin,fMax)
    @param fMin mínimo del intervalo
    @param fMax máximo del intervalo
    @return dato double aleatorio
*/
double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int main(int argc, char* argv[]) {

    const int VACAS_DEFAULT=1000;
    const double MIN = -100000;
    const double MAX = 100000;

    srandom(time(0));

    int casos=VACAS_DEFAULT;
    string archivo="vacas.dat";

    if (argc > 1) {

        archivo = argv[1];

        if (argc > 2)
            casos=atoi(argv[2]);
    }

    ofstream salida;
    salida.open(archivo,ofstream::trunc);
    if(!salida) {
        cerr << "ERROR: no se ha podido abrir " <<archivo << endl;
        exit(-1);
    }

    for (int i=0; i < casos; i++ )
        salida  << fRand(MIN,MAX)
                << "\t" << fRand(MIN,MAX)
                << endl;
    
    salida.close();

    return 0;

}
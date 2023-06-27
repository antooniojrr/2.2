/*
    @name generador.cpp
    @author Antonio Rodríguez, David Kessler, Santiago López
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>

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

    const int PARADAS_DEFAULT=10;
    const double MIN = -1000;
    const double MAX = 1000;

    srandom(time(NULL));

    int casos=PARADAS_DEFAULT;
    string archivo="paradas.dat";

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
    
    salida << casos << endl;

    for (int i = 0; i < casos; i++ ){
        salida << setw(3) << i+1 << setw(10) <<fRand(MIN,MAX) << setw(10) <<fRand(MIN,MAX);
        salida << endl;
    }
    salida.close();

    return 0;

}
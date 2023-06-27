/*
    @name generador.cpp
    @author Antonio Rodríguez, David Kessler, Santiago López
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
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

    const int NODOS_DEFAULT=20;
    const double MIN = -10;
    const double MAX = 10;

    srandom(time(NULL));

    int casos=NODOS_DEFAULT;
    string archivo="nodos.dat";

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
        for (int j = i + 1; j < casos; j++){
            if (rand() % 2 == 1)
                salida  << i << "\t" << j << "\t" << fRand(MIN, MAX) << endl;
        }
    }
    salida.close();

    return 0;

}
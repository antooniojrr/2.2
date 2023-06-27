

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int iRand(int min, int max) { return ((rand()%(max-min)) + min); }

int main(int argc, char* argv[]) {
    const int N_DEFAULT = 10;
    const int DUR_MAX = 10;
    const int DUR_MIN = 1;
    const int PLAZO_MAX = 20;
    const int PEN_MAX = 200;
    const int PEN_MIN = 5;
    const string DEFAULT_FICH = "datos.dat";

    string fich=DEFAULT_FICH;
    int casos = N_DEFAULT;
    srandom(time(NULL));

    if (argc > 1) {
        casos = atoi(argv[1]);
        if (argc > 2)
            fich = argv[2];
    }

    ofstream salida;
    salida.open(fich,ofstream::trunc);
    if(!salida) {
        cerr << "ERROR: no se ha podido abrir " << fich << endl;
        exit(-1);
    }

    salida << casos << endl;

    int duracion;
    for (int i = 0; i < casos; i++) {
        duracion = iRand(DUR_MIN, DUR_MAX);
        salida << duracion << "\t" << iRand(duracion,PLAZO_MAX) << "\t";
        salida << iRand(PEN_MIN, PEN_MAX) << endl;
    }

    salida.close();

    return 0;

}